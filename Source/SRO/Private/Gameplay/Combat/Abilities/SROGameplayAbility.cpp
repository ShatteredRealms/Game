// Copyright Shattered Realms Online All Rights Reserved


#include "Gameplay/Combat/Abilities/SROGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_StartAbilityState.h"
#include "Gameplay/Character/FightingCharacter.h"
#include "Gameplay/Combat/Abilities/AbilityTags.h"
#include "SRO/SRO.h"

USROGameplayAbility::USROGameplayAbility(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ActivationBlockedTags.AddTag(DeadTag);
}

void USROGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bActivateOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

void USROGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		return;
	}

	if (CastTimeSeconds)
	{
		UAbilityTask_PlayMontageAndWait* Task =
			UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this,
				NAME_None,
				CastingMontage,
				1/CastTimeSeconds);

		Task->OnBlendOut.AddDynamic(this, &USROGameplayAbility::OnCastingCompleted);
		Task->OnCompleted.AddDynamic(this, &USROGameplayAbility::OnCastingCompleted);
		Task->OnInterrupted.AddDynamic(this, &USROGameplayAbility::OnCancelled);
		Task->OnCancelled.AddDynamic(this, &USROGameplayAbility::OnCancelled);
		Task->ReadyForActivation();
	}
	else
	{
		OnCastingCompleted();
	}
}

bool USROGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	AFightingCharacter* FightingCharacter = Cast<AFightingCharacter>(ActorInfo->OwnerActor);
	if (FightingCharacter == nullptr)
	{
		UE_LOG(LogSRO, Warning, TEXT("FightingCharacter actors can only activate abilities"))
		return false;
	}

	if (Requirements.Num() == 0)
	{
		return true;
	}

	for (const auto Requirement : Requirements)
	{
		float CurrentValue = Requirement.Key.GetNumericValue(FightingCharacter->GetSkillAttributeSet().Get());
		if (CurrentValue < Requirement.Value)
		{
			UE_LOG(LogSRO, Verbose, TEXT("Requirement %s needs %d but has %d."), *Requirement.Key.GetName(), CurrentValue, Requirement.Value)
			return false;
		}
	}
	
	return true;
}

void USROGameplayAbility::OnCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

int USROGameplayAbility::GetAbilityId() const
{
	return AbilityId;
}

void USROGameplayAbility::OnCastingCompleted()
{
	UAbilityTask_PlayMontageAndWait* Task =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this,
			NAME_None,
			CastMontage);

	Task->OnBlendOut.AddDynamic(this, &USROGameplayAbility::OnCastCompleted);
	Task->OnCompleted.AddDynamic(this, &USROGameplayAbility::OnCastCompleted);
	Task->OnInterrupted.AddDynamic(this, &USROGameplayAbility::OnCancelled);
	Task->OnCancelled.AddDynamic(this, &USROGameplayAbility::OnCancelled);
	Task->ReadyForActivation();
}

void USROGameplayAbility::OnCastCompleted_Implementation()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}
