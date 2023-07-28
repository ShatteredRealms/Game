// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

class ANPCSpawner;

UCLASS()
class SRO_API ANPC : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Spawning)
	FVector RoamOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Spawning)
	ANPCSpawner* Spawner;

public:
	// Sets default values for this character's properties
	ANPC();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes)
	TSubclassOf<AAIController> DefaultAIClass;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnTargetedChanged_Implementation() override;
	virtual void OnIsAttackedUpdated_Implementation() override;
	virtual void OnCurrentHealthUpdated_Implementation() override;
	virtual void OnMaxHealthUpdated_Implementation() override;
	
public:
	/** Set the spawner for this NPC. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetSpawner(ANPCSpawner* NewSpawner) { Spawner = NewSpawner; }

	/** Get the spawner for this NPC. This can safely be NULL. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ANPCSpawner* GetSpawner() { return Spawner; };
};
