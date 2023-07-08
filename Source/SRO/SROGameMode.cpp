// Copyright Epic Games, Inc. All Rights Reserved.

#include "SROGameMode.h"

#include "HttpModule.h"
#include "JWTGenerator.h"
#include "JWTPluginBPLibrary.h"
#include "SRO.h"
#include "SROCharacter.h"
#include "SROGameSession.h"
#include "SROGameState.h"
#include "SROPlayerController.h"
#include "SROPlayerState.h"
#include "TurboLinkGrpcConfig.h"
#include "TurboLinkGrpcManager.h"
#include "TurboLinkGrpcUtilities.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/TypeContainer.h"
#include "SSroGamebackend/ConnectionService.h"
#include "Util/SROWebLibrary.h"

ASROGameMode::ASROGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SRO/Core/Gameplay/BP_SROCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	static ConstructorHelpers::FClassFinder<AHUD> SROHUDBPClass(TEXT("/Game/SRO/Core/UI/BP_SROHud"));
	if (SROHUDBPClass.Class != NULL)
	{
		HUDClass = SROHUDBPClass.Class;
	}
	
	PlayerStateClass = ASROPlayerState::StaticClass();

	PlayerControllerClass = ASROPlayerController::StaticClass();

	GameStateClass = ASROGameState::StaticClass();

	GameSessionClass = ASROGameSession::StaticClass();

	AgonesSDK = CreateDefaultSubobject<UAgonesComponent>(TEXT("AgonesSDK"));
	
	Keycloak = NewObject<UKeycloak>();
}

UAgonesComponent* ASROGameMode::GetAgonesSDK(UObject* WorldContextObject)
{
	if (const ASROGameMode* GameMode = Cast<ASROGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		return GameMode->AgonesSDK;
	}

	return nullptr;
}

void ASROGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	// Get the server Name
#if UE_BUILD_DEVELOPMENT
	ServerName = "localhost";
#else
	FGameServerDelegate GameServerSuccessDelegate;
	GameServerSuccessDelegate.BindDynamic(this, &ASROGameMode::OneGameServerDetailsReceived);
	AgonesSDK->GameServer(GameServerSuccessDelegate, {});
#endif

	// Setup keycloak
	Keycloak->OnKeycloakError().BindUObject(this, &ASROGameMode::OnKeycloakError);
	Keycloak->OnRefreshAuthToken().BindUObject(this, &ASROGameMode::UpdateAuthTokens);
	Keycloak->UpdateJWKs();
	
	GetWorldTimerManager().SetTimer(
		TokenRefreshTimerHandle,
		this,
		&ASROGameMode::RequestUpdateTokens,
		60.f,
		true,
		60.f);

	ASROGameSession* GS = Cast<ASROGameSession>(GameSession);
	check(GS)
	const auto Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &ASROGameMode::OnServerCredentialsReceived);
	Keycloak->ClientLogin(GS->GetAuthClientId(), GS->GetAuthClientSecret(), Request);

	// Setup TLM
	auto TLM = UTurboLinkGrpcUtilities::GetTurboLinkGrpcManager(GetWorld());
	if (!TLM)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to load TurboLink GRPC Utilities"));
		return;
	}

	// Setup connection service
	auto ConnectionService = Cast<UConnectionService>(TLM->MakeService("ConnectionService"));
	if (!ConnectionService)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to create connection service"));
		return;
	}

	ConnectionServiceClient = ConnectionService->MakeClient();
	ConnectionServiceClient->OnVerifyConnectResponse.AddUniqueDynamic(this, &ASROGameMode::OnVerifyConnectResponseReceived);

#if UE_BUILD_DEVELOPMENT
	ConnectionService->Connect(UTurboLinkGrpcUtilities::GetTurboLinkGrpcConfig()->GetServiceEndPoint(TEXT("ConnectionServiceDev")));
#else
	ConnectionService->Connect(UTurboLinkGrpcUtilities::GetTurboLinkGrpcConfig()->GetServiceEndPoint(TEXT("ConnectionServiceProd")));
#endif

	
}


//@TODO: Validate the player isn't already logged in
void ASROGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	FString& ErrorMessage)
{
	// Check the connection token
	FString ConnectionToken = UGameplayStatics::ParseOption(Options, TEXT("t"));
	if (ConnectionToken.IsEmpty())
	{
		ErrorMessage = TEXT("No connection token given");
		return;
	}

	auto Handle = ConnectionServiceClient->InitVerifyConnect();
	FGrpcSroGamebackendVerifyConnectRequest Request;
	Request.ConnectionId = ConnectionToken;
	Request.ServerName = ServerName;
	const FPendingConnection PendingConnection{Options, Address, UniqueId};
	PendingConnections.Add(Handle, PendingConnection);
	ConnectionServiceClient->VerifyConnect(Handle, Request, AuthToken);

	// while (PendingConnections.Find(Handle)->Status == CONNECTING)
	// {
	// 	FGenericPlatformProcess::ConditionalSleep([this, Handle]
	// 	{
	// 		return PendingConnections.Find(Handle)->Status == CONNECTING;
	// 	}, 0.0);
	// }

	// auto PendingConnection = PendingConnections.Find(Handle);
	// if (PendingConnection->Status == REJECTED)
	// {
	// 	ErrorMessage = TEXT("Connection rejected");
	// 	return;
	// }

	// Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

APlayerController* ASROGameMode::SpawnPlayerControllerCommon(ENetRole InRemoteRole, FVector const& SpawnLocation,
	FRotator const& SpawnRotation, TSubclassOf<APlayerController> InPlayerControllerClass)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;	// We never want to save player controllers into a map
	SpawnInfo.bDeferConstruction = true;
	APlayerController* NewPC = GetWorld()->SpawnActor<APlayerController>(InPlayerControllerClass, SpawnLocation, SpawnRotation, SpawnInfo);
	if (NewPC)
	{
		if (InRemoteRole == ROLE_SimulatedProxy)
		{
			// This is a local player because it has no authority/autonomous remote role
			NewPC->SetAsLocalPlayerController();
		}

		UGameplayStatics::FinishSpawningActor(NewPC, FTransform(SpawnRotation, SpawnLocation));
	}

	return NewPC;
}

FString ASROGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
                                    const FString& Options, const FString& Portal)
{
	auto CharacterDetails = AcceptedConnections.Find(UniqueId);
	if (!CharacterDetails)
	{
		return FString(TEXT("Connection not expected"));
	}
	
	check(NewPlayerController);

	// The player needs a PlayerState to register successfully
	if (NewPlayerController->PlayerState == nullptr)
	{
		return FString(TEXT("PlayerState is null"));
	}

	// Register the player with the session
	GameSession->RegisterPlayer(NewPlayerController, UniqueId, false);

	// Change the name
	ChangeName(NewPlayerController, CharacterDetails->Name, false);
	
	// Set the position
	FString ErrorMessage;
	if (!CharacterDetails->Location)
	{
		if (!UpdatePlayerStartSpot(NewPlayerController, Portal, ErrorMessage))
		{
			UE_LOG(LogGameMode, Warning, TEXT("InitNewPlayer: %s"), *ErrorMessage);
		}
	}
	else
	{
		FRotator StartRotation(0, 0, 0);
		FVector Location(CharacterDetails->Location->X, CharacterDetails->Location->Y, CharacterDetails->Location->Z);
		NewPlayerController->SetInitialLocationAndRotation(Location, StartRotation);
	}

	AcceptedConnections.Remove(UniqueId);

	return ErrorMessage;
}

void ASROGameMode::OnKeycloakError(const FString& Error)
{
	UE_LOG(LogSRO, Warning, TEXT("keycloak: %s"), *Error);
}

void ASROGameMode::OnVerifyConnectResponseReceived(
	FGrpcContextHandle Handle,
	const FGrpcResult& GrpcResult,
	const FGrpcSroCharactersCharacterDetails& Response)
{
	const auto PendingConnection = PendingConnections.Find(Handle);
	FString ErrorMessage = GrpcResult.Message;
	
	if (!PendingConnection)
	{
		ErrorMessage = "Unable to find verification handle";
	}
	else
	{
		if (!GrpcResult.Message.Equals("") || GrpcResult.Code != EGrpcResultCode::Ok)
		{
			ErrorMessage = GrpcResult.Message;
		}
		else
		{
			AcceptedConnections.Add(PendingConnection->UniqueId, Response);
		}
	}

	PendingConnections.Remove(Handle);
	
	Super::PreLogin(PendingConnection->Options, PendingConnection->Address, PendingConnection->UniqueId, ErrorMessage);
}

void ASROGameMode::OneGameServerDetailsReceived(const FGameServerResponse& Response)
{
	ServerName = Response.ObjectMeta.Name;
}

void ASROGameMode::OnServerCredentialsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	const FString Message = USROWebLibrary::ValidateJsonResponse(bWasSuccessful, Response, JsonObject); 
	if (Message != TEXT(""))
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get server client credentials"))
		return;
	}

	AuthToken = JsonObject->GetStringField("access_token");
	RefreshToken = JsonObject->GetStringField("refresh_token");
}

void ASROGameMode::UpdateAuthTokens(const FString& NewAuthToken, const FString& NewRefreshToken)
{
	AuthToken = NewAuthToken;
	RefreshToken = NewRefreshToken;
}

void ASROGameMode::RequestUpdateTokens()
{
	if (!RefreshToken.IsEmpty())
	{
		UE_LOG(LogSRO, Display, TEXT("Requesting new auth tokens"));
		Keycloak->RefreshAuthToken(RefreshToken);
	}
}
