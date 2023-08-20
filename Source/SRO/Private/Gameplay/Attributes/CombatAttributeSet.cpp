// Copyright Shattered Realms Online All Rights Reserved


#include "Gameplay/Attributes/CombatAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UCombatAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, Level, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, Mana, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, MaxMana, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, AttackRating, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, ProjectileArmorRating, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, MeleeArmorRating, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, FireArmorRating, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, FrostArmorRating, COND_OwnerOnly, REPNOTIFY_Always);
}

void UCombatAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

		GA_SET_IF(Level,					1, 15)
	GA_SET_ELSEIF(Health,					0, 1e6)
	GA_SET_ELSEIF(MaxHealth,				0, 1e6)
	GA_SET_ELSEIF(Mana,						0, 1e6)
	GA_SET_ELSEIF(MaxMana,					0, 1e6)
	GA_SET_ELSEIF(AttackRating,				-5000, 5000)
	GA_SET_ELSEIF(ProjectileArmorRating,	-5000, 5000)
	GA_SET_ELSEIF(MeleeArmorRating,			-5000, 5000)
	GA_SET_ELSEIF(FireArmorRating,			-5000, 5000)
	GA_SET_ELSEIF(FrostArmorRating,			-5000, 5000)
}
void UCombatAttributeSet::OnRep_Level(const FGameplayAttributeData& OldLevel)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatAttributeSet, Level, OldLevel);
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
