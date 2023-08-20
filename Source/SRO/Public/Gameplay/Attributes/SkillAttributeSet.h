// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Gameplay/Data/SkillData.h"
#include "UObject/NoExportTypes.h"
#include "SkillAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API USkillAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Strength, Category="Core")
	FGameplayAttributeData Strength;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Stamina, Category="Core")
	FGameplayAttributeData Stamina;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Agility, Category="Core")
	FGameplayAttributeData Agility;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Perception, Category="Core")
	FGameplayAttributeData Perception;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Intelligence, Category="Core")
	FGameplayAttributeData Intelligence;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Insight, Category="Core")
	FGameplayAttributeData Insight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MartialArts, Category="Melee")
	FGameplayAttributeData MartialArts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_OneHandMelee, Category="Melee")
	FGameplayAttributeData OneHandMelee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_TwoHandMelee, Category="Melee")
	FGameplayAttributeData TwoHandMelee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MultiMelee, Category="Melee")
	FGameplayAttributeData MultiMelee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MeleeInitiative, Category="Melee")
	FGameplayAttributeData MeleeInitiative;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_QuickSlash, Category="Melee|Special")
	FGameplayAttributeData QuickSlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Smash, Category="Melee|Special")
	FGameplayAttributeData Smash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Flurry, Category="Melee|Special")
	FGameplayAttributeData Flurry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Pistol, Category="Ranged")
	FGameplayAttributeData Pistol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Rifle, Category="Ranged")
	FGameplayAttributeData Rifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Sniper, Category="Ranged")
	FGameplayAttributeData Sniper;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_RangedInitiative, Category="Ranged")
	FGameplayAttributeData RangedInitiative;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_QuickShot, Category="Ranged|Special")
	FGameplayAttributeData QuickShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_PrecisionShot, Category="Ranged|Special")
	FGameplayAttributeData PrecisionShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Burst, Category="Ranged|Special")
	FGameplayAttributeData Burst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Creation, Category="Magic")
	FGameplayAttributeData Creation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Metamorphosis, Category="Magic")
	FGameplayAttributeData Metamorphosis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Remedy, Category="Magic")
	FGameplayAttributeData Remedy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Rejuvenation, Category="Magic")
	FGameplayAttributeData Rejuvenation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_SpaceTime, Category="Magic")
	FGameplayAttributeData SpaceTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Enhancement, Category="Magic")
	FGameplayAttributeData Enhancement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MagicInitiative, Category="Magic")
	FGameplayAttributeData MagicInitiative;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Programming, Category="Tradeskilling")
	FGameplayAttributeData Programming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Construction, Category="Tradeskilling")
	FGameplayAttributeData Construction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Engineering, Category="Tradeskilling")
	FGameplayAttributeData Engineering;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_LockPicking, Category="Tradeskilling")
	FGameplayAttributeData LockPicking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Treatment, Category="Defense")
	FGameplayAttributeData Treatment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_FirstAid, Category="Defense")
	FGameplayAttributeData FirstAid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Constitution, Category="Defense")
	FGameplayAttributeData Constitution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ManaPool, Category="Defense")
	FGameplayAttributeData ManaPool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MovementSpeed, Category="Adventuring")
	FGameplayAttributeData MovementSpeed;

public:
	FGameplayAttributeData& GetAttributeData(ESkill Skill);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Strength);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Strength);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Strength);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Strength);
	
	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Stamina);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Stamina);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Stamina);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Stamina);
	
	UFUNCTION()
	virtual void OnRep_Agility(const FGameplayAttributeData& OldAgility);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Agility);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Agility);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Agility);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Agility);
	
	UFUNCTION()
	virtual void OnRep_Perception(const FGameplayAttributeData& OldPerception);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Perception);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Perception);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Perception);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Perception);
	
	UFUNCTION()
	virtual void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Intelligence);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Intelligence);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Intelligence);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Intelligence);
	
	UFUNCTION()
	virtual void OnRep_Insight(const FGameplayAttributeData& OldInsight);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Insight);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Insight);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Insight);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Insight);
	
	UFUNCTION()
	virtual void OnRep_MartialArts(const FGameplayAttributeData& OldMartialArts);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, MartialArts);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MartialArts);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MartialArts);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MartialArts);
	
	UFUNCTION()
	virtual void OnRep_OneHandMelee(const FGameplayAttributeData& OldOneHandMelee);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, OneHandMelee);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(OneHandMelee);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(OneHandMelee);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(OneHandMelee);
	
	UFUNCTION()
	virtual void OnRep_TwoHandMelee(const FGameplayAttributeData& OldTwoHandMelee);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, TwoHandMelee);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(TwoHandMelee);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(TwoHandMelee);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(TwoHandMelee);
	
	UFUNCTION()
	virtual void OnRep_MultiMelee(const FGameplayAttributeData& OldMultiMelee);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, MultiMelee);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MultiMelee);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MultiMelee);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MultiMelee);
	
	UFUNCTION()
	virtual void OnRep_MeleeInitiative(const FGameplayAttributeData& OldMeleeInitiative);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, MeleeInitiative);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MeleeInitiative);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MeleeInitiative);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MeleeInitiative);
	
	UFUNCTION()
	virtual void OnRep_QuickSlash(const FGameplayAttributeData& OldQuickSlash);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, QuickSlash);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(QuickSlash);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(QuickSlash);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(QuickSlash);
	
	UFUNCTION()
	virtual void OnRep_Smash(const FGameplayAttributeData& OldSmash);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Smash);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Smash);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Smash);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Smash);
	
	UFUNCTION()
	virtual void OnRep_Flurry(const FGameplayAttributeData& OldFlurry);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Flurry);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Flurry);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Flurry);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Flurry);
	
	UFUNCTION()
	virtual void OnRep_Pistol(const FGameplayAttributeData& OldPistol);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Pistol);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Pistol);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Pistol);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Pistol);
	
	UFUNCTION()
	virtual void OnRep_Rifle(const FGameplayAttributeData& OldRifle);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Rifle);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Rifle);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Rifle);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Rifle);
	
	UFUNCTION()
	virtual void OnRep_Sniper(const FGameplayAttributeData& OldSniper);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Sniper);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Sniper);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Sniper);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Sniper);
	
	UFUNCTION()
	virtual void OnRep_RangedInitiative(const FGameplayAttributeData& OldRangedInitiative);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, RangedInitiative);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(RangedInitiative);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(RangedInitiative);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(RangedInitiative);
	
	UFUNCTION()
	virtual void OnRep_QuickShot(const FGameplayAttributeData& OldQuickShot);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, QuickShot);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(QuickShot);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(QuickShot);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(QuickShot);
	
	UFUNCTION()
	virtual void OnRep_PrecisionShot(const FGameplayAttributeData& OldPrecisionShot);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, PrecisionShot);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PrecisionShot);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PrecisionShot);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PrecisionShot);
	
	UFUNCTION()
	virtual void OnRep_Burst(const FGameplayAttributeData& OldBurst);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Burst);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Burst);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Burst);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Burst);
	
	UFUNCTION()
	virtual void OnRep_Creation(const FGameplayAttributeData& OldCreation);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Creation);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Creation);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Creation);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Creation);
	
	UFUNCTION()
	virtual void OnRep_Metamorphosis(const FGameplayAttributeData& OldMetamorphosis);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Metamorphosis);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Metamorphosis);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Metamorphosis);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Metamorphosis);
	
	UFUNCTION()
	virtual void OnRep_Remedy(const FGameplayAttributeData& OldRemedy);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Remedy);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Remedy);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Remedy);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Remedy);
	
	UFUNCTION()
	virtual void OnRep_Rejuvenation(const FGameplayAttributeData& OldRejuvenation);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Rejuvenation);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Rejuvenation);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Rejuvenation);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Rejuvenation);
	
	UFUNCTION()
	virtual void OnRep_SpaceTime(const FGameplayAttributeData& OldSpaceTime);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, SpaceTime);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(SpaceTime);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(SpaceTime);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(SpaceTime);
	
	UFUNCTION()
	virtual void OnRep_Enhancement(const FGameplayAttributeData& OldEnhancement);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Enhancement);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Enhancement);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Enhancement);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Enhancement);
	
	UFUNCTION()
	virtual void OnRep_MagicInitiative(const FGameplayAttributeData& OldMagicInitiative);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, MagicInitiative);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MagicInitiative);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MagicInitiative);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MagicInitiative);
	
	UFUNCTION()
	virtual void OnRep_Programming(const FGameplayAttributeData& OldProgramming);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Programming);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Programming);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Programming);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Programming);
	
	UFUNCTION()
	virtual void OnRep_Construction(const FGameplayAttributeData& OldConstruction);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Construction);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Construction);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Construction);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Construction);
	
	UFUNCTION()
	virtual void OnRep_Engineering(const FGameplayAttributeData& OldEngineering);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Engineering);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Engineering);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Engineering);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Engineering);
	
	UFUNCTION()
	virtual void OnRep_LockPicking(const FGameplayAttributeData& OldLockPicking);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, LockPicking);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(LockPicking);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(LockPicking);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(LockPicking);
	
	UFUNCTION()
	virtual void OnRep_Treatment(const FGameplayAttributeData& OldTreatment);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Treatment);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Treatment);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Treatment);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Treatment);
	
	UFUNCTION()
	virtual void OnRep_FirstAid(const FGameplayAttributeData& OldFirstAid);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, FirstAid);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(FirstAid);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(FirstAid);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(FirstAid);
	
	UFUNCTION()
	virtual void OnRep_Constitution(const FGameplayAttributeData& OldConstitution);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, Constitution);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Constitution);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Constitution);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Constitution);
	
	UFUNCTION()
	virtual void OnRep_ManaPool(const FGameplayAttributeData& OldManaPool);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, ManaPool);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(ManaPool);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(ManaPool);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(ManaPool);
	
	UFUNCTION()
	virtual void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USkillAttributeSet, MovementSpeed);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MovementSpeed);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MovementSpeed);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MovementSpeed);
};
