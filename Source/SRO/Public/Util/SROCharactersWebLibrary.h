// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SROCharactersWebLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API USROCharactersWebLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void Connect(int32 CharacterId, FString AuthToken, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request);

	static void GetCharacters(FString UserId, FString AuthToken, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request);
	
	static void CreateCharacter(TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request, FString AuthToken, FString OwnerId, FString Name, FString Gender, FString
	                            Realm, FString Dimension);
};
