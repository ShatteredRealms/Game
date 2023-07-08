// Copyright 2022 Shattered Realms Online

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "SROGameSession.generated.h"

/**
 * 
 */
UCLASS(Config=Game)
class SRO_API ASROGameSession : public AGameSession
{
	GENERATED_BODY()

public:
	UPROPERTY(Config)
	FString AuthClientIdDev;
	
	UPROPERTY(Config)
	FString AuthClientSecretDev;

	UPROPERTY(Config)
	FString AuthClientIdProd;
	
	UPROPERTY(Config)
	FString AuthClientSecretProd;

	UFUNCTION(BlueprintCallable, Category = "Auth")
	FString GetAuthClientId();

	UFUNCTION(BlueprintCallable, Category = "Auth")
	FString GetAuthClientSecret();
};
