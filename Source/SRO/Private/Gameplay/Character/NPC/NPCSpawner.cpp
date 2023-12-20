// Copyright Shattered Realms Online All Rights Reserved


#include "Gameplay/Character/NPC/NPCSpawner.h"

#include "NavigationSystem.h"
#include "Gameplay/Character/FightingCharacter.h"
#include "Components/SphereComponent.h"
#include "SRO/SRO.h"

// Sets default values
ANPCSpawner::ANPCSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bNetLoadOnClient = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnVolume = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnVolume"));
	SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

bool ANPCSpawner::ShouldSpawnMore() const
{
	return NPCs.Num() < MaximumCount;
}

FVector ANPCSpawner::GetCenter() const
{
	return SpawnVolume->GetComponentLocation();
}

float ANPCSpawner::GetRadius() const
{
	return SpawnVolume->GetScaledSphereRadius();
}

void ANPCSpawner::OnNPCDeath(AFightingCharacter* DamageTarget)
{
	ANPC* NPC = CastChecked<ANPC>(DamageTarget);
	NPCs.Remove(NPC);

	AttemptSpawnMore();
}

void ANPCSpawner::BeginPlay()
{
	Super::BeginPlay();

	// Spawn maximum NPCs
	for (int i = 0; i < MaximumCount; i++)
	{
		SpawnActor();
	}
}

void ANPCSpawner::OnSpawnTimerEnd()
{
	if (ShouldSpawnMore())
	{
		SpawnActor(true);
	}
}

ANPC* ANPCSpawner::SpawnActor(bool ContinueSpawning, bool ForceSpawn)
{
	if (!ForceSpawn && !ShouldSpawnMore())
	{
		return nullptr;
	}
	
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Owner = this;
	ActorSpawnParameters.bNoFail = true;
	ActorSpawnParameters.bAllowDuringConstructionScript = true;
	FTransform SpawnLocation = GetRandomSpawnTransform();
	ANPC* NewNPC = GetWorld()->SpawnActor<ANPC>(NPCClass, SpawnLocation, ActorSpawnParameters);
	if (NewNPC == nullptr)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to spawn actor"))
		return NewNPC;
	}

	// @TODO(wil): Re-add this
	// NewNPC->OnTakeFatalDamage.AddDynamic(this, &ANPCSpawner::OnNPCDeath);
	NewNPC->SpawnDefaultController();
	NewNPC->SetSpawner(this);
	
	NPCs.Add(NewNPC);
	
	if (ContinueSpawning)
	{
		AttemptSpawnMore();
	}
	
	return NewNPC;
}

void ANPCSpawner::AttemptSpawnMore()
{
	if (!ShouldSpawnMore())
	{
		return;
	}
	
	// If below the minimum count, then immediately spawn more and continue spawning
	if (NPCs.Num() < MinimumCount)
	{
		SpawnActor(true);
		return;
	}
	
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ANPCSpawner::OnSpawnTimerEnd, SpawnDelaySeconds, false);
}

FVector ANPCSpawner::GetRandomLocation() 
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (NavSys)
	{
		FNavLocation RandomLocation;
		NavSys->GetRandomReachablePointInRadius(GetCenter(), GetRadius(), RandomLocation);
		return RandomLocation.Location;
	}

	return FVector::ZeroVector;
}

FRotator ANPCSpawner::GetRandomYawRotator() const
{
	return FRotator{
		0,
		FMath::RandRange(0.f, 360.f),
		0,
	};
}

FTransform ANPCSpawner::GetRandomSpawnTransform()
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetRandomLocation());
	SpawnTransform.SetRotation(FQuat(GetRandomYawRotator()));
	return SpawnTransform;
}

