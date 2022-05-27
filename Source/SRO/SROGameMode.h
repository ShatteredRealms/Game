// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AgonesComponent.h"
#include "GameFramework/GameModeBase.h"
#include "SROGameMode.generated.h"

UCLASS(minimalapi, Config = "GameMode")
class ASROGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	/** The JWT public key used to verify JWT tokens from SRO services */
	UPROPERTY(Config)
	FString JWTPublicKey;

	/**
	 * The JWT private key used to sign JWT tokens for authentication and authorization between
	 * SRO services
	 */
	UPROPERTY(Config)
	FString JWTPrivateKey;
	
public:
	/** Agones SDK */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAgonesComponent* AgonesSDK;

	/** Default constructor that setups the base components */
	ASROGameMode();

	/** Gets the AgonesSDK from */
	UFUNCTION(BlueprintCallable)
	static UAgonesComponent* GetAgonesSDK(UObject* WorldContextObject);
};


