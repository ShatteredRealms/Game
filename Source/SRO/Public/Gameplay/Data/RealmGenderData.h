// Copyright Shattered RealmGenderGenders Online All Rights Reserved

#pragma once
#include "Engine/DataTable.h"
#include "RealmGenderData.generated.h"

USTRUCT(BlueprintType)
struct FRealmGenderData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle Realm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle Gender;
};
