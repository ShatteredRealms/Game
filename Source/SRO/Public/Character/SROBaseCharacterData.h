// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SSroCharacters/CharactersMessage.h"
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
	FGrpcSroCharactersGender Gender;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGrpcSroCharactersRealm Realm;

	// @TODO(wil): Data about character face, hair, etc ...
};
