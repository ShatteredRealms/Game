// Copyright Shattered Realms Online All Rights Reserved

#pragma once
#include "Engine/DataTable.h"
#include "SkillData.generated.h"

USTRUCT(BlueprintType)
struct FSkillData : public FTableRowBase
{
	GENERATED_BODY()

	/** Name of the skill */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	
	/** Category for the skill */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle Category;

	/** Description of what the skill is used for */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	////////////////////////////////
	// START CORE SKILL DEPENDENCIES
	
	/** Relative dependency on strength */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StrengthDependency;

	/** Relative dependency on stamina */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StaminaDependency;

	/** Relative dependency on agility */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AgilityDependency;

	/** Relative dependency on perception */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PerceptionDependency;

	/** Relative dependency on intelligence */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int IntelligenceDependency;

	/** Relative dependency on insight */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int InsightDependency;

	// END CORE SKILL DEPENDENCIES
	//////////////////////////////

	//////////////////////////////
	// START OCCUPATION MULTIPLIER 

	/** Relative dependency on insight */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TinkerMultiplier;
	
	// END OCCUPATION MULTIPLIER
	////////////////////////////
};
