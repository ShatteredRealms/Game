// Copyright 2022 Shattered Realms Online

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/SRORace.h"
#include "DataTypes/SROGender.h"
#include "GameFramework/Character.h"
#include "SROOfflineCharacter.generated.h"

USTRUCT(BlueprintType)
struct FSROOfflineCharacterInfo
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
	FSRORace Race;;	
};

UCLASS(BlueprintType, Blueprintable)
class SRO_API USROOfflineCharacter : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSROOfflineCharacterInfo OfflineCharacterInfo;
};
