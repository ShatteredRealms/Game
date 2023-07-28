// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "UObject/NoExportTypes.h"
#include "SkillAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API USkillAttributeSet : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core")
	FGameplayAttributeData Strength;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core")
	FGameplayAttributeData Stamina;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core")
	FGameplayAttributeData Agility;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core")
	FGameplayAttributeData Perception;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core")
	FGameplayAttributeData Intelligence;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core")
	FGameplayAttributeData Insight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Melee")
	FGameplayAttributeData MartialArts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Melee")
	FGameplayAttributeData OneHandMelee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Melee")
	FGameplayAttributeData TwoHandMelee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Melee")
	FGameplayAttributeData MultiMelee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Melee|Special")
	FGameplayAttributeData QuickSlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Melee|Special")
	FGameplayAttributeData Smash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Melee|Special")
	FGameplayAttributeData Flurry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ranged")
	FGameplayAttributeData Pistol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ranged")
	FGameplayAttributeData Rifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ranged")
	FGameplayAttributeData Sniper;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ranged|Special")
	FGameplayAttributeData QuickShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ranged|Special")
	FGameplayAttributeData PrecisionShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ranged|Special")
	FGameplayAttributeData Burst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Magic")
	FGameplayAttributeData Creation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Magic")
	FGameplayAttributeData Metamorphasis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Magic")
	FGameplayAttributeData Remedy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Magic")
	FGameplayAttributeData Rejuvenation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Magic")
	FGameplayAttributeData SpaceTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Magic")
	FGameplayAttributeData Enhancement;

public:
};
