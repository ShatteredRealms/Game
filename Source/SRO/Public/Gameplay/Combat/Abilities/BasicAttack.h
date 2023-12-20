// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SROGameplayAbility.h"
#include "BasicAttack.generated.h"

/**
 * Basic attacked used for all characters
 */
UCLASS()
class SRO_API UBasicAttack : public USROGameplayAbility
{
	GENERATED_BODY()

public:
	UBasicAttack(const FObjectInitializer& ObjectInitializer);
};
