// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Animation/AnimInstance.h"
#include "GameplayEffectTypes.h"
#include "SROAnimInstance.generated.h"

class UAbilitySystemComponent;

/**
 * Standard UAnimInstance for SRO. Tracks gameplay tags to remove the need to manually query them.
 */
UCLASS(Config = Game)
class USROAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	/** Standard object initializer */
	USROAnimInstance(const FObjectInitializer& ObjectInitializer);

protected:

#if WITH_EDITOR
	/** Checks if the gameplay tag property map is valid */
	virtual EDataValidationResult IsDataValid(TArray<FText>& ValidationErrors) override;
#endif // WITH_EDITOR

	/** Initializes the gameplay tag property map */
	virtual void NativeInitializeAnimation() override;

protected:

	/**
	 * Gameplay tags that can be mapped to blueprint variables. The variables will automatically update as the tags are
	 * added or removed. These should be used instead of manually querying for the gameplay tags.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "GameplayTags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;
};
