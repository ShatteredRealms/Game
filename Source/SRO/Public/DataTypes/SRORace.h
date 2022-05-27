#pragma once
#include "UObject/ObjectMacros.h"
#include "SRORace.generated.h"

USTRUCT(BlueprintType)
struct FSRORace
{
	GENERATED_BODY()

	/** The database ID */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Description;
};
