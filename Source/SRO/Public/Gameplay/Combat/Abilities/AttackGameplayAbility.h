// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Combat/Abilities/SROGameplayAbility.h"
#include "AttackGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API UAttackGameplayAbility : public USROGameplayAbility
{
	GENERATED_BODY()

protected:
	/** The minimum damage the ability can generate */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Combat")
	float DamageMin;

	/** The maximum damage the ability can generate */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Combat")
	float DamageMax;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GenerateDamageAmount() const;
};
