// Copyright Shattered Descriptions Online All Rights Reserved

#pragma once
#include "Engine/DataTable.h"
#include "SimpleData.generated.h"

USTRUCT(BlueprintType)
struct FSimpleData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
};
