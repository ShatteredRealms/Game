// Copyright Shattered Realms Online All Rights Reserved


#include "Gameplay/Combat/Abilities/ToggleAbility.h"

void UToggleAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)
		|| bIsActive)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		bIsActive = false;
		return;
	}
	
	
}
