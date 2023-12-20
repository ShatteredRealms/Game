// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Combat/Abilities/SROGameplayAbility.h"
#include "ToggleAbility.generated.h"

/**
 * Ability that is automatically ended if triggered while currently active.
 */
UCLASS()
class SRO_API UToggleAbility : public USROGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
