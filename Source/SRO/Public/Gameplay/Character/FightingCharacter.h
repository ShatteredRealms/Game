// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "BaseCharacter.h"
#include "Gameplay/Attributes/CombatAttributeSet.h"
#include "Gameplay/Attributes/SkillAttributeSet.h"
#include "FightingCharacter.generated.h"


#define GAMEPLAYATTRIBUTE_ACTOR_GETTER(AttributeSetName, PropertyName, CategoryName) \
	UFUNCTION(BlueprintCallable, Category="Attributes|##CategoryName##")\
	FORCEINLINE float Get##PropertyName##() const \
	{ \
		if (##AttributeSetName##.IsValid()) \
		{ \
		    return AttributeSetName##->Get##PropertyName##();\
		} \
		return 0.f; \
	};

/**
 * Base SRO character that cant attack and be attacked. It has combat and skill attribute sets.
 */
UCLASS(Blueprintable, BlueprintType)
class SRO_API AFightingCharacter : public ABaseCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
protected:
	/** Ability System Component. Required to use Gameplay Attributes and Gameplay Abilities. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;
	
	/** Fighting target of this. Null if not fighting. */
	UPROPERTY(ReplicatedUsing=OnRep_FightingTarget, VisibleAnywhere, BlueprintReadOnly, Category=Targeting)
	TObjectPtr<AFightingCharacter> FightingTarget;

	UFUNCTION()
	void OnRep_FightingTarget(AFightingCharacter* OldFightingTarget);

	/** Skill attributes for the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skills")
	TWeakObjectPtr<USkillAttributeSet> SkillAttributes;

	/** Combat attributes for the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	TWeakObjectPtr<UCombatAttributeSet> CombatAttributes;
	
public:
	/** Setup ability system, skill attributes and combat attributes. */
	AFightingCharacter(const FObjectInitializer& ObjectInitializer);

	/** Gets the ability system component for this character */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** Setup replicated properties */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Manages damage taken */
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/** Whether the character is attacking or not */
	UFUNCTION(BlueprintCallable, Category = Combat)
	FORCEINLINE bool IsAttacking() const { return FightingTarget != nullptr; }

	/** Attempts to start attacking the target */
	UFUNCTION(BlueprintCallable, Category = Combat)
	virtual void StartFighting(AFightingCharacter* Target);

	/** Attempts to stop fighting */
	UFUNCTION(BlueprintCallable, Category = Combat)
	virtual void StopFighting();

	/** Server: Start fighting the given target */
	UFUNCTION(Server, Reliable, WithValidation)
	void HandleStartFighting(AFightingCharacter* Target);

	/** Server: Stop fighting the current target */
	UFUNCTION(Server, Reliable, WithValidation)
	void HandleStopFighting();

	/** Gets the current fighting target */
	UFUNCTION(BlueprintCallable, Category = Combat)
	FORCEINLINE AFightingCharacter* GetFightingTarget() const { return FightingTarget; }

	UFUNCTION(BlueprintNativeEvent, Category=Targeting)
	void OnFightingTargetUpdated();

	/** Gets the rotation necessary to look at the fighting target */
	UFUNCTION(BlueprintCallable, Category=Targeting)
	FRotator GetFightingTargetRotation() const;

	/** Gets the skill attribute set for the character */
	FORCEINLINE TWeakObjectPtr<USkillAttributeSet> GetSkillAttributeSet() const { return SkillAttributes; }

	/** Gets the combat attribute set for the character */
	FORCEINLINE TWeakObjectPtr<UCombatAttributeSet> GetCombatAttributeSet() const { return CombatAttributes; }
	
	// START skill and combat attribute helpers
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(CombatAttributes, Level, Combat)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(CombatAttributes, Health, Combat)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(CombatAttributes, MaxHealth, Combat)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(CombatAttributes, Mana, Combat)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(CombatAttributes, MaxMana, Combat)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(CombatAttributes, AttackRating, Combat)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(CombatAttributes, ProjectileArmorRating, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(CombatAttributes, MeleeArmorRating, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(CombatAttributes, FireArmorRating, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(CombatAttributes, FrostArmorRating, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Strength, Core)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Stamina, Core)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Agility, Core)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Perception, Core)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Intelligence, Core)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Insight, Core)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, MartialArts, Melee)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, OneHandMelee, Melee)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, TwoHandMelee, Melee)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, MultiMelee, Melee)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, MeleeInitiative, Melee)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, QuickSlash, Melee|Special)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Smash, Melee|Special)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Flurry, Melee|Special)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Pistol, Ranged)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Rifle, Ranged)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Sniper, Ranged)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, RangedInitiative, Ranged)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, QuickShot, Ranged|Special)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, PrecisionShot, Ranged|Special)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Burst, Ranged|Special)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Creation, Magic)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Metamorphosis, Magic)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Remedy, Magic)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Rejuvenation, Magic)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, SpaceTime, Magic)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Enhancement, Magic)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, MagicInitiative, Magic)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Programming, Tradeskilling)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Construction, Tradeskilling)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Engineering, Tradeskilling)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, LockPicking, Tradeskilling)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Treatment, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, FirstAid, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, Constitution, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, ManaPool, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(SkillAttributes, MovementSpeed, Adventuring)
	// END skill and combat attribute helpers
};

