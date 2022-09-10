#pragma once
#include "UObject/ObjectMacros.h"
#include "SRORealm.generated.h"

USTRUCT(BlueprintType)
struct FSRORealm
{
	GENERATED_BODY()

	/** The database ID */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int64 Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Description;
};
