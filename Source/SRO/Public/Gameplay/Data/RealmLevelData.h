// Copyright Shattered Realms Online All Rights Reserved

#pragma once
#include "Engine/DataTable.h"
#include "RealmLevelData.generated.h"

USTRUCT(BlueprintType)
struct FRealmLevelData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Leveling")
	FDataTableRowHandle Level;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Leveling")
	int32 BonusHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Leveling")
	int32 BonusDefense;
};
