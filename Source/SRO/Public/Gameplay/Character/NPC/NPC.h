// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AIController.h"
#include "Gameplay/Character/FightingCharacter.h"
#include "Gameplay/Attributes/SkillAttributeSet.h"
#include "NPC.generated.h"

class ANPCSpawner;

UCLASS()
class SRO_API ANPC : public AFightingCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Spawning)
	FVector RoamOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Spawning)
	ANPCSpawner* Spawner;

public:
	// Sets default values for this character's properties
	ANPC(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes)
	TSubclassOf<AAIController> DefaultAIClass;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/** Set the spawner for this NPC. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetSpawner(ANPCSpawner* NewSpawner) { Spawner = NewSpawner; }

	/** Get the spawner for this NPC. This can safely be NULL. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ANPCSpawner* GetSpawner() { return Spawner; };
};
