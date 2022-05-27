#pragma once

#include "UObject/ObjectMacros.h"
#include "SROGender.h"
#include "SRORealm.h"
#include "SROBaseCharacter.generated.h"

USTRUCT(BlueprintType)
struct FSROBaseCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSROGender Gender;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSRORealm Realm;
};
