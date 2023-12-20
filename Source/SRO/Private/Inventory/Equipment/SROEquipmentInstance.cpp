// Copyright Shattered Realms Online All Rights Reserved


#include "Inventory/Equipment/SROEquipmentInstance.h"

#include "GameFramework/Character.h"
#include "Inventory/Equipment/SROEquipment.h"
#include "Net/UnrealNetwork.h"

USROEquipmentInstance::USROEquipmentInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USROEquipmentInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(USROEquipmentInstance, Instigator);
	DOREPLIFETIME(USROEquipmentInstance, SpawnedActors);
}

UWorld* USROEquipmentInstance::GetWorld() const
{
	if (APawn* OwningPawn = GetPawn())
	{
		return OwningPawn->GetWorld();
	}
	else
	{
		return nullptr;
	}
}

APawn* USROEquipmentInstance::GetPawn() const
{
	return Cast<APawn>(GetOuter());
}

APawn* USROEquipmentInstance::GetTypedPawn(TSubclassOf<APawn> PawnType) const
{
	APawn* Result = nullptr;
	if (UClass* ActualPawnType = PawnType)
	{
		if (GetOuter()->IsA(ActualPawnType))
		{
			Result = Cast<APawn>(GetOuter());
		}
	}
	
	return Result;
}

void USROEquipmentInstance::SpawnEquipmentActors(const TArray<FSROEquipmentActorToSpawn>& ActorsToSpawn)
{
	if (APawn* OwningPawn = GetPawn())
	{
		USceneComponent* AttachTarget = OwningPawn->GetRootComponent();
		if (ACharacter* Char = Cast<ACharacter>(OwningPawn))
		{
			AttachTarget = Char->GetMesh();
		}

		for (const FSROEquipmentActorToSpawn& SpawnInfo : ActorsToSpawn)
		{
			AActor* NewActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnInfo.ActorToSpawn, FTransform::Identity, OwningPawn);
			NewActor->FinishSpawning(FTransform::Identity, true);
			NewActor->SetActorRelativeTransform(SpawnInfo.AttachTransform);
			NewActor->AttachToComponent(AttachTarget, FAttachmentTransformRules::KeepRelativeTransform, SpawnInfo.AttachSocket);

			SpawnedActors.Add(NewActor);
		}
	}
}

void USROEquipmentInstance::DestroyEquipmentActors()
{
}

void USROEquipmentInstance::OnEquipped()
{
	K2_OnEquipped();
}

void USROEquipmentInstance::OnUnequipped()
{
	K2_OnUnequipped();
}
