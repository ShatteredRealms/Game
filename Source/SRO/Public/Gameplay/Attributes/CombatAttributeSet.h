// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeHelpers.h"
#include "AttributeSet.h"
#include "UObject/NoExportTypes.h"
#include "CombatAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API UCombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHealth, Category="Combat")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category="Combat")
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxMana, Category="Combat")
	FGameplayAttributeData MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Mana, Category="Combat")
	FGameplayAttributeData Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_AttackRating, Category="Combat")
	FGameplayAttributeData AttackRating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ProjectileArmorRating, Category="Defense")
	FGameplayAttributeData ProjectileArmorRating;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MeleeArmorRating, Category="Defense")
	FGameplayAttributeData MeleeArmorRating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_FireArmorRating, Category="Defense")
	FGameplayAttributeData FireArmorRating;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_FrostArmorRating, Category="Defense")
	FGameplayAttributeData FrostArmorRating;

public:
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCombatAttributeSet, Health);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_SETTER_WITHMIN(Health, 0);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);
	
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCombatAttributeSet, MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_SETTER_WITHMIN(MaxHealth, 0);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxHealth);
	
	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCombatAttributeSet, Mana);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Mana);
	GAMEPLAYATTRIBUTE_VALUE_SETTER_WITHMIN(Mana, 0);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Mana);
	
	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCombatAttributeSet, MaxMana);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxMana);
	GAMEPLAYATTRIBUTE_VALUE_SETTER_WITHMIN(MaxMana, 0);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxMana);
	
	UFUNCTION()
	virtual void OnRep_AttackRating(const FGameplayAttributeData& OldAttackRating);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCombatAttributeSet, AttackRating);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(AttackRating);
	GAMEPLAYATTRIBUTE_VALUE_SETTER_WITHMIN(AttackRating, 0);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(AttackRating);
	
	UFUNCTION()
	virtual void OnRep_ProjectileArmorRating(const FGameplayAttributeData& OldProjectileArmorRating);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCombatAttributeSet, ProjectileArmorRating);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(ProjectileArmorRating);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(ProjectileArmorRating);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(ProjectileArmorRating);
	
	UFUNCTION()
	virtual void OnRep_MeleeArmorRating(const FGameplayAttributeData& OldMeleeArmorRating);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCombatAttributeSet, MeleeArmorRating);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MeleeArmorRating);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MeleeArmorRating);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MeleeArmorRating);
	
	UFUNCTION()
	virtual void OnRep_FireArmorRating(const FGameplayAttributeData& OldFireArmorRating);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCombatAttributeSet, FireArmorRating);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(FireArmorRating);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(FireArmorRating);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(FireArmorRating);
	
	UFUNCTION()
	virtual void OnRep_FrostArmorRating(const FGameplayAttributeData& OldFrostArmorRating);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCombatAttributeSet, FrostArmorRating);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(FrostArmorRating);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(FrostArmorRating);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(FrostArmorRating);
};
