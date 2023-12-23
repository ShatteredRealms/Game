// Copyright Shattered Realms Online All Rights Reserved


#include "Gameplay/Combat/Abilities/AttackGameplayAbility.h"

#include "Kismet/KismetMathLibrary.h"

float UAttackGameplayAbility::GenerateDamageAmount() const
{
	return FMath::FRandRange(DamageMin, DamageMax);
}
