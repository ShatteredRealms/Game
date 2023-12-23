// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "BaseCharacter.h"
#include "Gameplay/Abilities/SROAbilitySet.h"
#include "Gameplay/Attributes/CombatAttributeSet.h"
#include "Gameplay/Attributes/SkillAttributeSet.h"
#include "Inventory/Equipment/SROEquipmentComponent.h"
#include "FightingCharacter.generated.h"


#define GAMEPLAYATTRIBUTE_ACTOR_GETTER(AttributeSetName, PropertyName, Combat) \
	UFUNCTION(BlueprintCallable, Category="Attributes")\
	FORCEINLINE float Get##PropertyName##() const \
	{ \
		const U##AttributeSetName##AttributeSet* AttributeSet = Get##AttributeSetName##AttributeSet(); \
		if (IsValid(AttributeSet)) \
		{ \
		    return AttributeSet->Get##PropertyName##();\
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
	
	/** Inventory component for the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory", meta = (AllowPrivateAccess = "true"))
	class USROEquipmentComponent* EquipmentComponent;
	
	/** Fighting target of this. Null if not fighting. */
	UPROPERTY(ReplicatedUsing=OnRep_FightingTarget, VisibleAnywhere, BlueprintReadOnly, Category=Targeting)
	TObjectPtr<AFightingCharacter> FightingTarget;

	UFUNCTION()
	void OnRep_FightingTarget(AFightingCharacter* OldFightingTarget);
	
public:
	/** Setup ability system, skill attributes and combat attributes. */
	AFightingCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

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

	/** Called when the server fighting target is updated */
	UFUNCTION(BlueprintNativeEvent, Category=Targeting)
	void OnFightingTargetUpdated();

	/** Gets the rotation necessary to look at the fighting target */
	UFUNCTION(BlueprintCallable, Category=Targeting)
	FRotator GetFightingTargetRotation() const;

	/** Gets the skill attribute set for the character */
	FORCEINLINE const USkillAttributeSet* GetSkillAttributeSet() const { return AbilitySystemComponent->GetSet<USkillAttributeSet>(); }

	/** Gets the combat attribute set for the character */
	FORCEINLINE const UCombatAttributeSet* GetCombatAttributeSet() const { return AbilitySystemComponent->GetSet<UCombatAttributeSet>(); }

	/** Gets the equipment component for the character */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE USROEquipmentComponent* GetEquipmentComponent() const { return EquipmentComponent; }

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USROEquipment> DefaultNoWeapon;
	
	// START skill and combat attribute helpers
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Combat, Level, Combat)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Combat, Health, Combat)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Combat, MaxHealth, Combat)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Combat, Mana, Combat)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Combat, MaxMana, Combat)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Combat, AttackRating, Combat)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Combat, ProjectileArmorRating, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Combat, MeleeArmorRating, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Combat, FireArmorRating, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Combat, FrostArmorRating, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Strength, Core)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Stamina, Core)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Agility, Core)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Perception, Core)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Intelligence, Core)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Insight, Core)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, MartialArts, Melee)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, OneHandMelee, Melee)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, TwoHandMelee, Melee)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, MultiMelee, Melee)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, MeleeInitiative, Melee)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, QuickSlash, Melee|Special)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Smash, Melee|Special)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Flurry, Melee|Special)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Pistol, Ranged)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Rifle, Ranged)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Sniper, Ranged)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, RangedInitiative, Ranged)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, QuickShot, Ranged|Special)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, PrecisionShot, Ranged|Special)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Burst, Ranged|Special)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Creation, Magic)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Metamorphosis, Magic)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Remedy, Magic)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Rejuvenation, Magic)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, SpaceTime, Magic)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Enhancement, Magic)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, MagicInitiative, Magic)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Programming, Tradeskilling)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Construction, Tradeskilling)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Engineering, Tradeskilling)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, LockPicking, Tradeskilling)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Treatment, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, FirstAid, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, Constitution, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, ManaPool, Defense)
	GAMEPLAYATTRIBUTE_ACTOR_GETTER(Skill, MovementSpeed, Adventuring)
	// END skill and combat attribute helpers
};

