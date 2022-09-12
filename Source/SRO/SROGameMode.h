// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AgonesComponent.h"
#include "JWTVerifier.h"
#include "GameFramework/GameModeBase.h"
#include "SROGameMode.generated.h"

UENUM(BlueprintType)
enum FConnectionStatus
{
	CONNECTING,
	REJECTED,
	ACCEPTED,
};

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

	UPROPERTY()
	UJWTVerifier* JWTVerifier;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, TEnumAsByte<FConnectionStatus>> PendingConnections;
	
	/** Agones SDK */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAgonesComponent* AgonesSDK;

	/** Default constructor that setups the base components */
	ASROGameMode();

	/** Gets the AgonesSDK from */
	UFUNCTION(BlueprintCallable)
	static UAgonesComponent* GetAgonesSDK(UObject* WorldContextObject);

	/** Validates the AuthToken has access for the CharacterName. If fails removes the connection */
	UFUNCTION(BlueprintCallable)
	bool ValidateAuthToken(const FString& Token, const FString& CharacterName);

	/** Renews the AuthToken */
	UFUNCTION(BlueprintCallable)
	FString RenewAuthToken(const FString& OldAuthToken);

	/** Gets the user id for the AuthToken */
	UFUNCTION(BlueprintCallable)
	int32 GetAuthTokenSubject(const FString& AuthToken);

private:
	void OnCharactersReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

public:
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;
};



