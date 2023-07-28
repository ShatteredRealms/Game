// Copyright Shattered Realms Online All Rights Reserved

#pragma once
#include "Engine/DataTable.h"
#include "LevelUpData.generated.h"

USTRUCT(BlueprintType)
struct FLevelUpData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Leveling")
	int32 RequiredXP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Leveling")
	int32 SkillPointsGained;
};
