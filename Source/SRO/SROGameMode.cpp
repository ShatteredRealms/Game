// Copyright Epic Games, Inc. All Rights Reserved.

#include "SROGameMode.h"

#include "HttpModule.h"
#include "JWTGenerator.h"
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
#include "SSroCharacter/CharacterService.h"
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
	else
	{
		DefaultPawnClass = ASROCharacter::StaticClass();
	}
	
	static ConstructorHelpers::FClassFinder<AHUD> SROHUDBPClass(TEXT("/Game/SRO/Core/UI/BP_SROHud"));
	if (SROHUDBPClass.Class != NULL)
	{
		HUDClass = SROHUDBPClass.Class;
	}
	else
	{
		HUDClass = ASROHud::StaticClass();
	}
	
	static ConstructorHelpers::FClassFinder<ASROPlayerController> SROPlayerControllerBPClass(TEXT("/Game/SRO/Core/Gameplay/BP_SROPlayerController"));
	if (SROPlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = SROPlayerControllerBPClass.Class;
	}
	else
	{
		PlayerControllerClass = ASROPlayerController::StaticClass();
	}
	
	PlayerStateClass = ASROPlayerState::StaticClass();

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

void ASROGameMode::OnEditCharacterResponseReceived(
	FGrpcContextHandle Handle,
	const FGrpcResult& GrpcResult,
	const FGrpcGoogleProtobufEmpty& Response)
{
	if (GrpcResult.Code != EGrpcResultCode::Ok)
	{
		UE_LOG(LogSRO, Error, TEXT("Failed to edit character: %s"), *GrpcResult.Message)
		return;
	}
	
	UE_LOG(LogSRO, Display, TEXT("Edit character successful"));
}

void ASROGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	// Get the server Name
#if UE_BUILD_DEVELOPMENT
	ServerName = "localhost";
	AgonesMapName = "Scene_Demo";
#else
	FGameServerDelegate GameServerSuccessDelegate;
	GameServerSuccessDelegate.BindDynamic(this, &ASROGameMode::OnGameServerDetailsReceived);
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

	// Setup connection service
	auto CharacterService = Cast<UCharacterService>(TLM->MakeService("CharacterService"));
	if (!CharacterService)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to create connection service"));
		return;
	}

	CharacterServiceClient = CharacterService->MakeClient();
	CharacterServiceClient->OnEditCharacterResponse.AddUniqueDynamic(this, &ASROGameMode::OnEditCharacterResponseReceived);

#if UE_BUILD_DEVELOPMENT
	CharacterService->Connect(UTurboLinkGrpcUtilities::GetTurboLinkGrpcConfig()->GetServiceEndPoint(TEXT("CharacterServiceDev")));
#else
	CharacterService->Connect(UTurboLinkGrpcUtilities::GetTurboLinkGrpcConfig()->GetServiceEndPoint(TEXT("CharacterServiceProd")));
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
	FGrpcSroCharacterCharacterDetails* CharacterDetails = AcceptedConnections.Find(UniqueId);
	if (!CharacterDetails)
	{
		return FString(TEXT("Connection not expected"));
	}
	
	check(NewPlayerController);

	// The player needs a PlayerState to register successfully
	auto PlayerState = Cast<ASROPlayerState>(NewPlayerController->PlayerState);
	if (!PlayerState)
	{
		return FString(TEXT("PlayerState is null"));
	}

	// Register the player with the session
	GameSession->RegisterPlayer(NewPlayerController, UniqueId, false);

	// Change the name
	ChangeName(NewPlayerController, CharacterDetails->Name, false);
	
	// Set the position
	FString ErrorMessage;
	if (CharacterDetails->Location.World == "")
	{
		UE_LOG(LogSRO, Warning, TEXT("Location world not set"));
		if (!UpdatePlayerStartSpot(NewPlayerController, Portal, ErrorMessage))
		{
			UE_LOG(LogSRO, Warning, TEXT("InitNewPlayer: %s"), *ErrorMessage);
		}
		
		PlayerState->StartingLocation = NewPlayerController->StartSpot->GetActorLocation();
		PlayerState->StartingRotation = NewPlayerController->StartSpot->GetActorRotation();
	}
	else
	{
		UE_LOG(LogSRO, Warning, TEXT("Loading previous player position"));
		PlayerState->StartingLocation = FVector(
			CharacterDetails->Location.X,
			CharacterDetails->Location.Y,
			CharacterDetails->Location.Z);
		PlayerState->StartingRotation = FRotator(
			CharacterDetails->Location.Pitch,
			CharacterDetails->Location.Yaw,
			CharacterDetails->Location.Roll);
	}

	auto Character = Cast<ASROCharacter>(NewPlayerController->GetCharacter());
	if (Character)
	{
		return ErrorMessage; 
	}
	
	return ErrorMessage;
}

void ASROGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	auto Character = Cast<ASROCharacter>(NewPlayer->GetCharacter());
	if (!Character)
	{
		return;
	}

	auto Details = AcceptedConnections.Find(NewPlayer->NetConnection->PlayerId);
	if (!Details)
	{
		return;
	}

	Character->SetBaseCharacter(*Details);
	
	AcceptedConnections.Remove(NewPlayer->NetConnection->PlayerId);
}

APawn* ASROGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
	auto PlayerState = Cast<ASROPlayerState>(NewPlayer->PlayerState);
	if (!PlayerState)
	{
		return Super::SpawnDefaultPawnFor_Implementation(NewPlayer, StartSpot);
	}
	
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.Owner = this;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;
	SpawnInfo.bDeferConstruction = false;
	
	APawn* NewPawn = GetWorld()->SpawnActor<APawn>(
		GetDefaultPawnClassForController(NewPlayer),
		PlayerState->StartingLocation,
		PlayerState->StartingRotation,
		SpawnInfo);
	
	return NewPawn;
}

void ASROGameMode::Logout(AController* Exiting)
{
	ASROPlayerController* PC = Cast<ASROPlayerController>(Exiting);
	if (!PC)
	{
		Super::Logout(Exiting);
		return;
	}
	
	SyncCharacter(PC);
}

void ASROGameMode::OnKeycloakError(const FString& Error)
{
	UE_LOG(LogSRO, Warning, TEXT("keycloak: %s"), *Error);
}

void ASROGameMode::OnVerifyConnectResponseReceived(
	FGrpcContextHandle Handle,
	const FGrpcResult& GrpcResult,
	const FGrpcSroCharacterCharacterDetails& Response)
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
	
	Super::PreLogin(PendingConnection->Options, PendingConnection->Address, PendingConnection->UniqueId, ErrorMessage);
}

void ASROGameMode::OnGameServerDetailsReceived(const FGameServerResponse& Response)
{
	ServerName = Response.ObjectMeta.Name;
	
	const auto MapNamePtr = Response.ObjectMeta.Labels.Find("map");
	if (MapNamePtr)
	{
		AgonesMapName = *MapNamePtr;
	}
	else
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get map name from server"));
	}
}

void ASROGameMode::SyncCharacter(ASROPlayerController* PC)
{
	auto Character = Cast<ASROCharacter>(PC->GetCharacter());
	if (!Character)
	{
		return;
	}

	FGrpcSroLocation Location;
	Location.World = AgonesMapName;
	Location.X = PC->GetPawn()->GetActorLocation().X;
	Location.Y = PC->GetPawn()->GetActorLocation().Y;
	Location.Z = PC->GetPawn()->GetActorLocation().Z;
	Location.Roll = PC->GetPawn()->GetActorRotation().Roll;
	Location.Pitch = PC->GetPawn()->GetActorRotation().Pitch;
	Location.Yaw = PC->GetPawn()->GetActorRotation().Yaw;
	
	FGrpcSroCharacterEditCharacterRequest Request;
	Request.Target.Type.TypeCase = EGrpcSroCharacterCharacterTargetType::Id;
	Request.Target.Type.Id = Character->GetCharacterDetails().Id;
	Request.Optional_location.Optional_locationCase = EGrpcSroCharacterEditCharacterRequestOptional_location::Location;
	Request.Optional_location.Location = Location;
	Request.Optional_play_time.PlayTime = Character->GetCharacterDetails().PlayTime + Character->GetPlayTimespan();
	
	const auto Handle = CharacterServiceClient->InitEditCharacter();
	CharacterServiceClient->EditCharacter(Handle, Request, AuthToken);

	PC->GetPawn()->Destroy();
	PC->SetPawn(nullptr);
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
	UE_LOG(LogSRO, Display, TEXT("Updated auth and refresh tokens"))
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
