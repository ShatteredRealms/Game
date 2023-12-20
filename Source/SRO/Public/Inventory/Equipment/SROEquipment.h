// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SROEquipment.generated.h"


class USROAbilitySet;
class USROEquipmentInstance;
USTRUCT()
struct FSROEquipmentActorToSpawn
{
	GENERATED_BODY()

public:
	FSROEquipmentActorToSpawn()
	{}

	UPROPERTY(EditAnywhere, Category=Equipment)
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category=Equipment)
	FName AttachSocket;

	UPROPERTY(EditAnywhere, Category=Equipment)
	FTransform AttachTransform;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Const, Abstract)
class SRO_API USROEquipment : public UObject
{
	GENERATED_BODY()

public:
	USROEquipment(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Class to spawn
	UPROPERTY(EditDefaultsOnly, Category=Equipment)
	TSubclassOf<USROEquipmentInstance> InstanceType;

	// Gameplay ability sets to grant when this is equipped
	UPROPERTY(EditDefaultsOnly, Category=Equipment)
	TArray<TObjectPtr<const USROAbilitySet>> AbilitySetsToGrant;
	
	// Actors to spawn on the pawn when this is equipped
	UPROPERTY(EditDefaultsOnly, Category=Equipment)
	TArray<FSROEquipmentActorToSpawn> ActorsToSpawn;
};
