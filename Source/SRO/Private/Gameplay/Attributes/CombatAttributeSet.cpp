// Copyright Shattered Realms Online All Rights Reserved


#include "Gameplay/Attributes/CombatAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UCombatAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, AttackRating, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, ProjectileArmorRating, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, MeleeArmorRating, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, FireArmorRating, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, FrostArmorRating, COND_None, REPNOTIFY_Always);
}

void UCombatAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(GetHealth());
	}
}

void UCombatAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatAttributeSet, Health, OldHealth);
}

void UCombatAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatAttributeSet, MaxHealth, OldMaxHealth);
}

void UCombatAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatAttributeSet, Mana, OldMana);
}

void UCombatAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatAttributeSet, MaxMana, OldMaxMana);
}

void UCombatAttributeSet::OnRep_AttackRating(const FGameplayAttributeData& OldAttackRating)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatAttributeSet, AttackRating, OldAttackRating);
}

void UCombatAttributeSet::OnRep_ProjectileArmorRating(const FGameplayAttributeData& OldProjectileArmorRating)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatAttributeSet, ProjectileArmorRating, OldProjectileArmorRating);
}

void UCombatAttributeSet::OnRep_MeleeArmorRating(const FGameplayAttributeData& OldMeleeArmorRating)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatAttributeSet, MeleeArmorRating, OldMeleeArmorRating);
}

void UCombatAttributeSet::OnRep_FireArmorRating(const FGameplayAttributeData& OldFireArmorRating)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatAttributeSet, FireArmorRating, OldFireArmorRating);
}

void UCombatAttributeSet::OnRep_FrostArmorRating(const FGameplayAttributeData& OldFrostArmorRating)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatAttributeSet, FrostArmorRating, OldFrostArmorRating);
}
