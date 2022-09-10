// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SROBaseCharacter.generated.h"

USTRUCT(BlueprintType)
struct FSROBaseCharacterStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GenderId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RealmId;

	FSROBaseCharacterStruct()
	{
	}

	explicit FSROBaseCharacterStruct(TSharedPtr<FJsonObject> JsonObject)
	{
		JsonObject->TryGetNumberField(TEXT("id"), Id);
		JsonObject->TryGetStringField(TEXT("name"), Name);
		JsonObject->TryGetNumberField(TEXT("gender"), GenderId);
		JsonObject->TryGetNumberField(TEXT("realm"), RealmId);
	}
};


/**
 * 
 */
UCLASS(Blueprintable)
class SRO_API USROBaseCharacter : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSROBaseCharacterStruct BaseData;
};
