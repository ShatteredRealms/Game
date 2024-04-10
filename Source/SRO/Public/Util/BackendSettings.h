// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BackendSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName="Web Backend Settings"))
class SRO_API UBackendSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "SRO API")
	FString ChatHTTPUrl = "http://localhost:8180/v1";

	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "SRO API")
	FString CharacterHTTPUrl = "http://localhost:8081/v1";

	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "SRO API")
	FString GameBackendHTTPUrl = "http://localhost:8082/v1";

	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "SRO API")
	FString ChatGRPCUrl = "http://localhost:8180";

	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "SRO API")
	FString CharacterGRPCUrl = "http://localhost:8081";

	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "SRO API")
	FString GameBackendGRPCUrl = "http://localhost:8082";
};
