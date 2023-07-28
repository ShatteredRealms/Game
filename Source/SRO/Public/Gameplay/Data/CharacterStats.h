// Copyright Shattered Realms Online All Rights Reserved

#pragma once
#include "Engine/DataTable.h"
#include "CharacterStats.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Leveling")
	int32 RequiredXP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Leveling")
	int32 SkillPointsGained;
};
