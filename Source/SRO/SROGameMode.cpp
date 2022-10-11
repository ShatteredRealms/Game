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
#include "Interfaces/IHttpResponse.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Util/SROCharactersWebLibrary.h"
#include "Util/SROWebLibrary.h"

ASROGameMode::ASROGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/CyberpunkSamurai/BP_CyberpunkSamurai"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerStateClass = ASROPlayerState::StaticClass();

	PlayerControllerClass = ASROPlayerController::StaticClass();

	GameStateClass = ASROGameState::StaticClass();

	GameSessionClass = ASROGameSession::StaticClass();

	AgonesSDK = CreateDefaultSubobject<UAgonesComponent>(TEXT("AgonesSDK"));

	FBase64::Decode(FPlatformMisc::GetEnvironmentVariable(TEXT("JWT_PUBLIC_KEY")), JWTPublicKey);
	FBase64::Decode(FPlatformMisc::GetEnvironmentVariable(TEXT("JWT_PRIVATE_KEY")), JWTPrivateKey);

	JWTVerifier = UJWTPluginBPLibrary::CreateVerifier(JWTPublicKey, EAlgorithm::rs256);
}

UAgonesComponent* ASROGameMode::GetAgonesSDK(UObject* WorldContextObject)
{
	if (const ASROGameMode* GameMode = Cast<ASROGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		return GameMode->AgonesSDK;
	}

	return nullptr;
}

void ASROGameMode::OnCharactersReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                                       bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	const FString Message = USROWebLibrary::ValidateJsonResponse(bWasSuccessful, Response, JsonObject);

	FRegexMatcher Matcher(FRegexPattern(".users\\/(\\d+)\\/."), Response->GetURL());
	int32 UserId = FCString::Atoi(*Matcher.GetCaptureGroup(1));
	
	PendingConnections.Emplace(UserId, Message == TEXT("") ? ACCEPTED : REJECTED);
}

void ASROGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	FString& ErrorMessage)
{
	FString AuthToken = UGameplayStatics::ParseOption(Options, TEXT("t"));

	if (AuthToken.IsEmpty())
	{
		ErrorMessage = TEXT("No auth token given");
		return;
	}

	FString CharacterName = UGameplayStatics::ParseOption(Options, TEXT("c"));
	
	if (CharacterName.IsEmpty())
	{
		ErrorMessage = TEXT("No character name given");
		return;
	}
	//
	// if (!ValidateAuthToken(AuthToken, CharacterName))
	// {
	// 	ErrorMessage = TEXT("Not authorized");;
	// 	return;
	// }

	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

APlayerController* ASROGameMode::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;	// We never want to save player controllers into a map
	SpawnInfo.bDeferConstruction = true;
	ASROPlayerController* NewPC = GetWorld()->SpawnActor<ASROPlayerController>(PlayerControllerClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);

	if (NewPC)
	{
		if (InRemoteRole == ROLE_SimulatedProxy)
		{
			// This is a local player because it has no authority/autonomous remote role
			NewPC->SetAsLocalPlayerController();
		}
		else
		{
			NewPC->AuthToken = RenewAuthToken(UGameplayStatics::ParseOption(Options, TEXT("t")));
		}

		UGameplayStatics::FinishSpawningActor(NewPC, FTransform(FRotator::ZeroRotator, FVector::ZeroVector));
	}

	return NewPC;
}

bool ASROGameMode::ValidateAuthToken(const FString& Token, const FString& CharacterName)
{
	if (!JWTVerifier->VerifyJWT(Token))
	{
		UE_LOG(LogSRO, Warning, TEXT("Invalid token in login request for %s"), *CharacterName)
		return false;
	}
	
	auto Claims = UJWTPluginBPLibrary::GetClaims(Token);
	const FString Sub = *Claims.Find("sub");
	int32 UserId = FCString::Atoi(*Sub);
	
	const auto Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &ASROGameMode::OnCharactersReceived);

	PendingConnections.Emplace(UserId, CONNECTING);
	USROCharactersWebLibrary::GetCharacters(UserId, Token, Request);

	FGenericPlatformProcess::ConditionalSleep([&]{ return PendingConnections.Find(UserId)->GetValue() != CONNECTING; }, 100);

	return PendingConnections.Find(UserId)->GetValue() != REJECTED;
}

FString ASROGameMode::RenewAuthToken(const FString& OldAuthToken)
{
	
	if (!JWTVerifier->VerifyJWT(OldAuthToken))
	{
		UE_LOG(LogSRO, Warning, TEXT("Invalid token to refresh."))
		return "";
	}
	
	auto OldClaims = UJWTPluginBPLibrary::GetClaims(OldAuthToken);
	
	auto JwtGenerator = UJWTPluginBPLibrary::CreateGenerator();
	JwtGenerator->AddClaims(OldClaims);
	JwtGenerator->AddClaim("iss", "gameserver.shatteredrealmsonline.com");
	JwtGenerator->ExpireAt(60*60);
	
	FString Jwt;
	
	JwtGenerator->GenerateToken(JWTPrivateKey, EAlgorithm::rs256, true, Jwt);
	
	return Jwt;
}

int32 ASROGameMode::GetAuthTokenSubject(const FString& AuthToken)
{
	if (!JWTVerifier->VerifyJWT(AuthToken))
	{
		return -1;
	}
	
	auto Claims = UJWTPluginBPLibrary::GetClaims(AuthToken);
	const FString Sub = *Claims.Find("sub");
	return FCString::Atoi(*Sub);
}