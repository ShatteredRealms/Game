// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "MeleeDamage.generated.h"

/**
 * 
 */
UCLASS(const, Blueprintable, BlueprintType)
class SRO_API UMeleeDamage : public UDamageType
{
	GENERATED_BODY()

public:
	UMeleeDamage();
};
