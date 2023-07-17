// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SROBaseCharacterData.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API USROBaseCharacterData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Gender;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Realm;

	// @TODO(wil): Data about character face, hair, etc ...
};
