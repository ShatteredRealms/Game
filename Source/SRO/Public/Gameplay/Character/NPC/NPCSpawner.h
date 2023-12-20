// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "GameFramework/Actor.h"
#include "NPCSpawner.generated.h"

/**
 * Actor that is placed in a level to handle spawning of one type of NPC within it's volume. NPCs will only ever be
 * spawned in path-able locations.
 */
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
	/** NPC class used when creating the actor */
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

	/** Timer used for spawning delays */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning|Timer")
	FTimerHandle SpawnTimerHandle;

	/** Volume which NPCs can be spawned in. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning|Volume")
	class USphereComponent* SpawnVolume;

public:
	/** Get all spawned actors */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TSet<ANPC*> GetSpawnedActors() { return NPCs; }

	/** Whether the spawner should spawn more NPCs */
	UFUNCTION(BlueprintCallable)
	bool ShouldSpawnMore() const;

	/** Gets the center of the spawner */
	UFUNCTION(BlueprintCallable)
	FVector GetCenter() const;

	/** Gets the radius of the spawner */
	UFUNCTION(BlueprintCallable)
	float GetRadius() const;
	
protected:
	/** Event delegate for when an NPC owned by this spawner dies. */
	UFUNCTION()
	void OnNPCDeath(AFightingCharacter* DamageTarget);
	
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Event delegate for when the spawn timer ends */
	UFUNCTION()
	void OnSpawnTimerEnd();
	
	/**
	 * Spawn another actor. If ContinueSpawning is true, then it set a timer to spawn another actor if the maximum
	 * amount isn't reached.
	 */
	UFUNCTION(BlueprintCallable)
	ANPC* SpawnActor(bool ContinueSpawning = false, bool ForceSpawn = true);

	/** Spawns more NPCs if necessary */
	UFUNCTION(BlueprintCallable)
	void AttemptSpawnMore();

private:
	// START HELPER FUNCTIONS
	
	/** Gets a random nav-able location within the spawn area. */
	FVector GetRandomLocation();
	
	/** Creates a random rotation with no pitch or roll. */
	FRotator GetRandomYawRotator() const;

	/** Creates a random spawn location and rotation */
	FTransform GetRandomSpawnTransform();
	
	// END HELPER FUNCTIONS
};
