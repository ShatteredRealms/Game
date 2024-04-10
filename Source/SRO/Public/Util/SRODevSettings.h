// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SRODevSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Developer Settings"))
class SRO_API USRODevSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/**
	 * Development builds ONLY.
	 *
	 * If set along with TestPassword, then will automatically sign-in as this user
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Auth")
	FText TestUserUsername;
	
	/**
	 * Development builds ONLY.
	 *
	 * If set along with TestUsername, then will automatically sign-in as this user
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Auth")
	FText TestUserPassword;
};
