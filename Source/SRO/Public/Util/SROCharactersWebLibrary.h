// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Character/SROBaseCharacter.h"
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
	static FString CharactersURL();

	static void GetCharacters(int32 UserId, FString AuthToken, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request);
};
