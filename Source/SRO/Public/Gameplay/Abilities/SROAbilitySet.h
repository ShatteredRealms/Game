// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActiveGameplayEffectHandle.h"
#include "Engine/DataAsset.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"

#include "GameplayAbilitySpecHandle.h"
#include "SROAbilitySet.generated.h"

class USROGameplayAbility;
class UAttributeSet;
class UGameplayEffect;
class UObject;


/**
 * FSROAbilitySet_GameplayAbility
 *
 *	Data used by the ability set to grant gameplay abilities.
 */
USTRUCT(BlueprintType)
struct FSROAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:

	// Gameplay ability to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USROGameplayAbility> Ability = nullptr;

	// Level of ability to grant.
	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	// Tag used to process input for the ability.
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};


/**
 * FSROAbilitySet_GameplayEffect
 *
 *	Data used by the ability set to grant gameplay effects.
 */
USTRUCT(BlueprintType)
struct FSROAbilitySet_GameplayEffect
{
	GENERATED_BODY()

public:

	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;

	// Level of gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.0f;
};

/**
 * FSROAbilitySet_AttributeSet
 *
 *	Data used by the ability set to grant attribute sets.
 */
USTRUCT(BlueprintType)
struct FSROAbilitySet_AttributeSet
{
	GENERATED_BODY()

public:
	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributeSet> AttributeSet;

};

/**
 * FSROAbilitySet_GrantedHandles
 *
 *	Data used to store handles to what has been granted by the ability set.
 */
USTRUCT(BlueprintType)
struct FSROAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:

	/** Adds ability spec handle if valid */
	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);

	/** Adds gameplay effect handle if valid */
	void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);

	/** Adds attribute set if valid */
	void AddAttributeSet(UAttributeSet* Set);

	/** Removes all abilities, gameplay effects, and attributes */
	void TakeFromAbilitySystem(UAbilitySystemComponent* ASC);

protected:

	/** Handles to the granted abilities. */
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	/** Handles to the granted gameplay effects. */
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

	/** Pointers to the granted attribute sets */
	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> GrantedAttributeSets;
};


/**
 * USROAbilitySet
 *
 *	Non-mutable data asset used to grant gameplay abilities and gameplay effects.
 */
UCLASS(BlueprintType, Const)
class USROAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	/** Default constructor */
	USROAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	 * Grants the ability set to the specified ability system component. The returned handles can be used later to take
	 * away anything that was granted.
	 */
	void GiveToAbilitySystem(UAbilitySystemComponent* ASC, FSROAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject = nullptr) const;

protected:

	/** Gameplay abilities to grant when this ability set is granted. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta=(TitleProperty=Ability))
	TArray<FSROAbilitySet_GameplayAbility> GrantedGameplayAbilities;

	/** Gameplay effects to grant when this ability set is granted. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects", meta=(TitleProperty=GameplayEffect))
	TArray<FSROAbilitySet_GameplayEffect> GrantedGameplayEffects;

	/** Attribute sets to grant when this ability set is granted. */
	UPROPERTY(EditDefaultsOnly, Category = "Attribute Sets", meta=(TitleProperty=AttributeSet))
	TArray<FSROAbilitySet_AttributeSet> GrantedAttributes;
};
