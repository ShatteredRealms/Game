// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SROGameplayAbility.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SRO_API USROGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Description")
	int AbilityId;
	
	/** Name of the ability shown in game */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Description")
	FString Name;
	
	/** In-game description of the ability */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Description")
	FString Description;
	
	/** The maximum distance between the source and the target */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Activation")
	float Range;

	/** How long it takes to cast. Instant if less than or equal to zero */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Activation")
	float CastTimeSeconds;

	/** Animation to play while casting. Length depends on CastTimeSeconds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Animation")
	UAnimMontage* CastingMontage;

	/** Animation after casting is finished. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Animation")
	UAnimMontage* CastMontage;

	/** Timer used for casting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Activation")
	FTimerHandle CastTimer;

	/** Requirements for the ability */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Requirements")
	TMap<FGameplayAttribute, float> Requirements;
	
public:
	USROGameplayAbility(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Activation")
	bool bActivateOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;

	/** The casting and cast animations have finished and everything else should be done */
	UFUNCTION(BlueprintNativeEvent)
	void OnCastCompleted();

	int GetAbilityId() const; 

protected:
	/** The casting animation (if any was needed) finished and cast will be called */
	UFUNCTION()
	virtual void OnCastingCompleted();

	UFUNCTION()
	virtual void OnCancelled();
};
