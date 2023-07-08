// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AgonesComponent.h"
#include "JWTVerifier.h"
#include "Auth/Keycloak/Keycloak.h"
#include "GameFramework/GameModeBase.h"
#include "SSroCharacters/CharactersMessage.h"
#include "SSroGamebackend/ConnectionClient.h"
#include "SROGameMode.generated.h"

USTRUCT(BlueprintType)
struct FPendingConnection
{
	GENERATED_BODY()

	UPROPERTY()
	FString Options;

	UPROPERTY()
	FString Address;

	UPROPERTY()
	FUniqueNetIdRepl UniqueId;

	UPROPERTY()
	FString ErrorMessage;
};

UCLASS(minimalapi, Config = "GameMode")
class ASROGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UConnectionServiceClient* ConnectionServiceClient;


private:
	UPROPERTY()
	UKeycloak* Keycloak;
	// FKeycloakAdapterErrorDelegate ErrorDelegate;
	// FKeycloakAdapterFinishedDelegate FinishedDelegate;
	// FKeycloakAdapterJWKFoundDelegate FoundJWKDelegate;
	
	FString ServerName;

	FTimerHandle TokenRefreshTimerHandle;
	FString AuthToken;
	FString RefreshToken;

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGrpcContextHandle, FPendingConnection> PendingConnections;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FUniqueNetIdRepl, FGrpcSroCharactersCharacterDetails> AcceptedConnections;
	
	/** Agones SDK */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAgonesComponent* AgonesSDK;

	/** Default constructor that setups the base components */
	ASROGameMode();

	/** Gets the AgonesSDK from */
	UFUNCTION(BlueprintCallable)
	static UAgonesComponent* GetAgonesSDK(UObject* WorldContextObject);

private:
	void OnCharactersReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual APlayerController* SpawnPlayerControllerCommon(ENetRole InRemoteRole, FVector const& SpawnLocation, FRotator const& SpawnRotation, TSubclassOf<APlayerController> InPlayerControllerClass) override;
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;
	
	void OnServerCredentialsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void UpdateAuthTokens(const FString& NewAuthToken, const FString& NewRefreshToken);
	void RequestUpdateTokens();

	UFUNCTION()
	void OnKeycloakError(const FString& Error);
	
	UFUNCTION()
	void OnVerifyConnectResponseReceived(FGrpcContextHandle Handle, const FGrpcResult& GrpcResult, const FGrpcSroCharactersCharacterDetails& Response);
	
	UFUNCTION()
	void OneGameServerDetailsReceived(const FGameServerResponse& Response);
};




