// Copyright Epic Games, Inc. All Rights Reserved.

#include "Inventory/Equipment/SROEquipmentComponent.h"

#include "AbilitySystemGlobals.h"
#include "Engine/ActorChannel.h"
#include "Inventory/Equipment/SROEquipment.h"
#include "Inventory/Equipment/SROEquipmentInstance.h"
#include "Net/UnrealNetwork.h"

class FLifetimeProperty;
struct FReplicationFlags;

//////////////////////////////////////////////////////////////////////
// FSROAppliedEquipmentEntry

FString FSROAppliedEquipmentEntry::GetDebugString() const
{
	return FString::Printf(TEXT("%s of %s"), *GetNameSafe(Instance), *GetNameSafe(Equipment.Get()));
}

//////////////////////////////////////////////////////////////////////
// FSROEquipmentList

void FSROEquipmentList::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
 	for (int32 Index : RemovedIndices)
 	{
 		const FSROAppliedEquipmentEntry& Entry = Entries[Index];
		if (Entry.Instance != nullptr)
		{
			Entry.Instance->OnUnequipped();
		}
 	}
}

void FSROEquipmentList::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	for (int32 Index : AddedIndices)
	{
		const FSROAppliedEquipmentEntry& Entry = Entries[Index];
		if (Entry.Instance != nullptr)
		{
			Entry.Instance->OnEquipped();
		}
	}
}

void FSROEquipmentList::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
// 	for (int32 Index : ChangedIndices)
// 	{
// 		const FGameplayTagStack& Stack = Stacks[Index];
// 		TagToCountMap[Stack.Tag] = Stack.StackCount;
// 	}
}

UAbilitySystemComponent* FSROEquipmentList::GetAbilitySystemComponent() const
{
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();
	return UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor);
}

USROEquipmentInstance* FSROEquipmentList::AddEntry(TSubclassOf<USROEquipment> Equipment)
{
	check(Equipment != nullptr);
 	check(OwnerComponent);
	check(OwnerComponent->GetOwner()->HasAuthority());
	
	const USROEquipment* EquipmentCDO = GetDefault<USROEquipment>(Equipment);

	TSubclassOf<USROEquipmentInstance> InstanceType = EquipmentCDO->InstanceType;
	if (InstanceType == nullptr)
	{
		InstanceType = USROEquipmentInstance::StaticClass();
	}
	
	FSROAppliedEquipmentEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Equipment = Equipment;
	NewEntry.Instance = NewObject<USROEquipmentInstance>(OwnerComponent->GetOwner(), InstanceType);  //@TODO: Using the actor instead of component as the outer due to UE-127172
	USROEquipmentInstance* Result = NewEntry.Instance;

	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		for (TObjectPtr<const USROAbilitySet> AbilitySet : EquipmentCDO->AbilitySetsToGrant)
		{
			AbilitySet->GiveToAbilitySystem(ASC, &NewEntry.GrantedHandles, Result);
		}
	}
	else
	{
		//@TODO: Warning logging?
	}

	Result->SpawnEquipmentActors(EquipmentCDO->ActorsToSpawn);

	MarkItemDirty(NewEntry);

	return Result;
}

void FSROEquipmentList::RemoveEntry(USROEquipmentInstance* Instance)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FSROAppliedEquipmentEntry& Entry = *EntryIt;
		if (Entry.Instance == Instance)
		{
			if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
			{
				Entry.GrantedHandles.TakeFromAbilitySystem(ASC);
			}

			Instance->DestroyEquipmentActors();
			EntryIt.RemoveCurrent();
			MarkArrayDirty();
			
			return;
		}
	}
}

//////////////////////////////////////////////////////////////////////
// USROEquipmentComponent

USROEquipmentComponent::USROEquipmentComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, EquipmentList(this)
{
	SetIsReplicatedByDefault(true);
	bWantsInitializeComponent = true;
}

void USROEquipmentComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, EquipmentList);
}

USROEquipmentInstance* USROEquipmentComponent::EquipItem(TSubclassOf<USROEquipment> EquipmentClass)
{
	USROEquipmentInstance* Result = nullptr;
	
	if (EquipmentClass != nullptr)
	{
		Result = EquipmentList.AddEntry(EquipmentClass);
		if (Result != nullptr)
		{
			Result->OnEquipped();

			if (IsUsingRegisteredSubObjectList() && IsReadyForReplication())
			{
				AddReplicatedSubObject(Result);
			}
		}
	}
	
	return Result;
}

void USROEquipmentComponent::UnequipItem(USROEquipmentInstance* ItemInstance)
{
	if (ItemInstance != nullptr)
	{
		if (IsUsingRegisteredSubObjectList())
		{
			RemoveReplicatedSubObject(ItemInstance);
		}

		ItemInstance->OnUnequipped();
		EquipmentList.RemoveEntry(ItemInstance);
	}
}

bool USROEquipmentComponent::ReplicateSubobjects(UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (FSROAppliedEquipmentEntry& Entry : EquipmentList.Entries)
	{
		USROEquipmentInstance* Instance = Entry.Instance;

		if (IsValid(Instance))
		{
			WroteSomething |= Channel->ReplicateSubobject(Instance, *Bunch, *RepFlags);
		}
	}

	return WroteSomething;
}

void USROEquipmentComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void USROEquipmentComponent::UninitializeComponent()
{
	TArray<USROEquipmentInstance*> AllEquipmentInstances;

	// gathering all instances before removal to avoid side effects affecting the equipment list iterator	
	for (const FSROAppliedEquipmentEntry& Entry : EquipmentList.Entries)
	{
		AllEquipmentInstances.Add(Entry.Instance);
	}

	for (USROEquipmentInstance* EquipInstance : AllEquipmentInstances)
	{
		UnequipItem(EquipInstance);
	}

	Super::UninitializeComponent();
}

void USROEquipmentComponent::ReadyForReplication()
{
	Super::ReadyForReplication();

	// Register existing SROEquipmentInstances
	if (IsUsingRegisteredSubObjectList())
	{
		for (const FSROAppliedEquipmentEntry& Entry : EquipmentList.Entries)
		{
			USROEquipmentInstance* Instance = Entry.Instance;

			if (IsValid(Instance))
			{
				AddReplicatedSubObject(Instance);
			}
		}
	}
}

USROEquipmentInstance* USROEquipmentComponent::GetFirstInstanceOfType(TSubclassOf<USROEquipmentInstance> InstanceType)
{
	for (FSROAppliedEquipmentEntry& Entry : EquipmentList.Entries)
	{
		if (USROEquipmentInstance* Instance = Entry.Instance)
		{
			if (Instance->IsA(InstanceType))
			{
				return Instance;
			}
		}
	}

	return nullptr;
}

TArray<USROEquipmentInstance*> USROEquipmentComponent::GetEquipmentInstancesOfType(TSubclassOf<USROEquipmentInstance> InstanceType) const
{
	TArray<USROEquipmentInstance*> Results;
	for (const FSROAppliedEquipmentEntry& Entry : EquipmentList.Entries)
	{
		if (USROEquipmentInstance* Instance = Entry.Instance)
		{
			if (Instance->IsA(InstanceType))
			{
				Results.Add(Instance);
			}
		}
	}
	return Results;
}


