// Copyright Epic Games, Inc. All Rights Reserved.

#include "SROGameMode.h"
#include "SROCharacter.h"
#include "SROGameSession.h"
#include "SROGameState.h"
#include "SROPlayerController.h"
#include "SROPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ASROGameMode::ASROGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerStateClass = ASROPlayerState::StaticClass();

	PlayerControllerClass = ASROPlayerController::StaticClass();

	// GameStateClass = ASROGameState::StaticClass();

	GameSessionClass = ASROGameSession::StaticClass();

	AgonesSDK = CreateDefaultSubobject<UAgonesComponent>(TEXT("AgonesSDK"));

	FBase64::Decode(FPlatformMisc::GetEnvironmentVariable(TEXT("JWT_PUBLIC_KEY")), JWTPublicKey);
	FBase64::Decode(FPlatformMisc::GetEnvironmentVariable(TEXT("JWT_PRIVATE_KEY")), JWTPrivateKey);
}

UAgonesComponent* ASROGameMode::GetAgonesSDK(UObject* WorldContextObject)
{
	if (const ASROGameMode* GameMode = Cast<ASROGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		return GameMode->AgonesSDK;
	}

	return nullptr;
}

