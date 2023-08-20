// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "GameFramework/Actor.h"
#include "NPCSpawner.generated.h"

UCLASS()
class SRO_API ANPCSpawner : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleInstanceOnly, Category=Actors)
	TSet<ANPC*> NPCs;
	
public:	
	// Sets default values for this actor's properties
	ANPCSpawner();

protected:
	/** . */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Spawning)
	TSubclassOf<ANPC> NPCClass;
	
	/** Minimum number of NPCs to have spawned. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Spawning)
	int MinimumCount = 0;

	/** Maximum number of NPCs that can be spawned.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Spawning)
	int MaximumCount = 10;

	/** Number of seconds to wait between spawning another NPC. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Spawning|Timer")
	float SpawnDelaySeconds = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning|Timer")
	FTimerHandle SpawnTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning|Volume")
	class USphereComponent* SpawnVolume;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TSet<ANPC*> GetSpawnedActors() { return NPCs; }

	UFUNCTION(BlueprintCallable)
	bool ShouldSpawnMore() const;

	UFUNCTION(BlueprintCallable)
	FVector GetCenter() const;

	UFUNCTION(BlueprintCallable)
	float GetRadius() const;
	
protected:
	/** Event delegate for when an NPC owned by this spawner dies. */
	UFUNCTION()
	void OnNPCDeath(AFightingCharacter* DamageTarget);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Event delegate for when the spawn timer ends */
	UFUNCTION()
	void OnSpawnTimerEnd();
	
	/**
	 * Spawn another actor. If ShouldSpawnMore is true, then it set a timer to spawn another actor if the maximum
	 * amount isn't reached.
	 */
	UFUNCTION(BlueprintCallable)
	ANPC* SpawnActor(bool ShouldSpawnMore = false);

	UFUNCTION(BlueprintCallable)
	void AttemptSpawnMore();

private:
	// START HELPER FUNCTIONS
	FVector GetRandomLocation();
	FRotator GetRandomYawRotator() const;
	FTransform GetRandomSpawnTransform();
	// END HELPER FUNCTIONS
};
