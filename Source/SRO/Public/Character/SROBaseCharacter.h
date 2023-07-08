// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SROBaseCharacterData.h"
#include "TurboLinkGrpcMessage.h"
#include "SSroCharacters/CharactersMessage.h"
#include "SROBaseCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SRO_API USROBaseCharacter : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGrpcSroCharactersCharacterDetails BaseData;
};
