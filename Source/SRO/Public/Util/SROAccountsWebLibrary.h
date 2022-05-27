// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SROAccountsWebLibrary.generated.h"

/**
 * 
 */
UCLASS(Config = Game)
class SHATTEREDREALMS_API USROAccountsWebLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Processes a login request to the backend auth servers given a request. */
	static void Login(const FString& Username, const FString& Password, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request);
};
