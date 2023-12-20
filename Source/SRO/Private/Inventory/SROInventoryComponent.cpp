// Copyright Epic Games, Inc. All Rights Reserved.

#include "Inventory/SROInventoryComponent.h"

#include "Engine/ActorChannel.h"
#include "Engine/World.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Inventory/SROInventoryItem.h"
#include "Inventory/SROInventoryItemInstance.h"
#include "NativeGameplayTags.h"
#include "Net/UnrealNetwork.h"

class FLifetimeProperty;
struct FReplicationFlags;

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_SRO_Inventory_Message_StackChanged, "SRO.Inventory.Message.StackChanged");

//////////////////////////////////////////////////////////////////////
// FSROInventoryEntry

FString FSROInventoryEntry::GetDebugString() const
{
	TSubclassOf<USROInventoryItem> ItemDef;
	if (Instance != nullptr)
	{
		ItemDef = Instance->GetItem();
	}

	return FString::Printf(TEXT("%s (%d x %s)"), *GetNameSafe(Instance), StackCount, *GetNameSafe(ItemDef));
}

//////////////////////////////////////////////////////////////////////
// FSROInventoryList

void FSROInventoryList::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	for (int32 Index : RemovedIndices)
	{
		FSROInventoryEntry& Stack = Entries[Index];
		BroadcastChangeMessage(Stack, /*OldCount=*/ Stack.StackCount, /*NewCount=*/ 0);
		Stack.LastObservedCount = 0;
	}
}

void FSROInventoryList::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	for (int32 Index : AddedIndices)
	{
		FSROInventoryEntry& Stack = Entries[Index];
		BroadcastChangeMessage(Stack, /*OldCount=*/ 0, /*NewCount=*/ Stack.StackCount);
		Stack.LastObservedCount = Stack.StackCount;
	}
}

void FSROInventoryList::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
	for (int32 Index : ChangedIndices)
	{
		FSROInventoryEntry& Stack = Entries[Index];
		check(Stack.LastObservedCount != INDEX_NONE);
		BroadcastChangeMessage(Stack, /*OldCount=*/ Stack.LastObservedCount, /*NewCount=*/ Stack.StackCount);
		Stack.LastObservedCount = Stack.StackCount;
	}
}

void FSROInventoryList::BroadcastChangeMessage(FSROInventoryEntry& Entry, int32 OldCount, int32 NewCount)
{
	FSROInventoryChangeMessage Message;
	Message.InventoryOwner = OwnerComponent;
	Message.Instance = Entry.Instance;
	Message.NewCount = NewCount;
	Message.Delta = NewCount - OldCount;

	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(OwnerComponent->GetWorld());
	MessageSystem.BroadcastMessage(TAG_SRO_Inventory_Message_StackChanged, Message);
}

USROInventoryItemInstance* FSROInventoryList::AddEntry(TSubclassOf<USROInventoryItem> ItemDef, int32 StackCount)
{
	USROInventoryItemInstance* Result = nullptr;

	check(ItemDef != nullptr);
 	check(OwnerComponent);

	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());


	FSROInventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Instance = NewObject<USROInventoryItemInstance>(OwnerComponent->GetOwner());  //@TODO: Using the actor instead of component as the outer due to UE-127172
	NewEntry.Instance->SetItem(ItemDef);
	for (USROInventoryItemFragment* Fragment : GetDefault<USROInventoryItem>(ItemDef)->Fragments)
	{
		if (Fragment != nullptr)
		{
			Fragment->OnInstanceCreated(NewEntry.Instance);
		}
	}
	NewEntry.StackCount = StackCount;
	Result = NewEntry.Instance;

	//const USROInventoryItem* ItemCDO = GetDefault<USROInventoryItem>(ItemDef);
	MarkItemDirty(NewEntry);

	return Result;
}

void FSROInventoryList::AddEntry(USROInventoryItemInstance* Instance)
{
	unimplemented();
}

void FSROInventoryList::RemoveEntry(USROInventoryItemInstance* Instance)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FSROInventoryEntry& Entry = *EntryIt;
		if (Entry.Instance == Instance)
		{
			EntryIt.RemoveCurrent();
			MarkArrayDirty();
		}
	}
}

TArray<USROInventoryItemInstance*> FSROInventoryList::GetAllItems() const
{
	TArray<USROInventoryItemInstance*> Results;
	Results.Reserve(Entries.Num());
	for (const FSROInventoryEntry& Entry : Entries)
	{
		if (Entry.Instance != nullptr) //@TODO: Would prefer to not deal with this here and hide it further?
		{
			Results.Add(Entry.Instance);
		}
	}
	return Results;
}

//////////////////////////////////////////////////////////////////////
// USROInventoryComponent

USROInventoryComponent::USROInventoryComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InventoryList(this)
{
	SetIsReplicatedByDefault(true);
}

void USROInventoryComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, InventoryList);
}

bool USROInventoryComponent::CanAddItem(TSubclassOf<USROInventoryItem> ItemDef, int32 StackCount)
{
	// Check for stacking
	if (ItemDef.GetDefaultObject()->CanStack()
		&& FindFirstItemStackBy(ItemDef))
	{
		return true;
	}
	
	return InventoryList.Entries.Num() < InventorySize;
}

USROInventoryItemInstance* USROInventoryComponent::AddItem(TSubclassOf<USROInventoryItem> ItemDef, int32 StackCount)
{
	if (!CanAddItem(ItemDef, StackCount))
	{
		return nullptr;
	}
	
	USROInventoryItemInstance* Result = nullptr;
	if (ItemDef != nullptr)
	{
		Result = InventoryList.AddEntry(ItemDef, StackCount);
		
		if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && Result)
		{
			AddReplicatedSubObject(Result);
		}
	}
	
	return Result;
}

void USROInventoryComponent::AddItemInstance(USROInventoryItemInstance* ItemInstance)
{
	InventoryList.AddEntry(ItemInstance);
	if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && ItemInstance)
	{
		AddReplicatedSubObject(ItemInstance);
	}
}

void USROInventoryComponent::RemoveItemInstance(USROInventoryItemInstance* ItemInstance)
{
	InventoryList.RemoveEntry(ItemInstance);

	if (ItemInstance && IsUsingRegisteredSubObjectList())
	{
		RemoveReplicatedSubObject(ItemInstance);
	}
}

TArray<USROInventoryItemInstance*> USROInventoryComponent::GetAllItems() const
{
	return InventoryList.GetAllItems();
}

USROInventoryItemInstance* USROInventoryComponent::FindFirstItemStackBy(TSubclassOf<USROInventoryItem> ItemDef) const
{
	for (const FSROInventoryEntry& Entry : InventoryList.Entries)
	{
		USROInventoryItemInstance* Instance = Entry.Instance;

		if (IsValid(Instance))
		{
			if (Instance->GetItem() == ItemDef)
			{
				return Instance;
			}
		}
	}

	return nullptr;
}

int32 USROInventoryComponent::GetTotalItemCountBy(TSubclassOf<USROInventoryItem> ItemDef) const
{
	int32 TotalCount = 0;
	for (const FSROInventoryEntry& Entry : InventoryList.Entries)
	{
		USROInventoryItemInstance* Instance = Entry.Instance;

		if (IsValid(Instance))
		{
			if (Instance->GetItem() == ItemDef)
			{
				++TotalCount;
			}
		}
	}

	return TotalCount;
}

bool USROInventoryComponent::ConsumeItemsBy(TSubclassOf<USROInventoryItem> ItemDef, int32 NumToConsume)
{
	AActor* OwningActor = GetOwner();
	if (!OwningActor || !OwningActor->HasAuthority())
	{
		return false;
	}

	//@TODO: N squared right now as there's no acceleration structure
	int32 TotalConsumed = 0;
	while (TotalConsumed < NumToConsume)
	{
		if (USROInventoryItemInstance* Instance = USROInventoryComponent::FindFirstItemStackBy(ItemDef))
		{
			InventoryList.RemoveEntry(Instance);
			++TotalConsumed;
		}
		else
		{
			return false;
		}
	}

	return TotalConsumed == NumToConsume;
}

void USROInventoryComponent::ReadyForReplication()
{
	Super::ReadyForReplication();

	// Register existing USROInventoryItemInstance
	if (IsUsingRegisteredSubObjectList())
	{
		for (const FSROInventoryEntry& Entry : InventoryList.Entries)
		{
			USROInventoryItemInstance* Instance = Entry.Instance;

			if (IsValid(Instance))
			{
				AddReplicatedSubObject(Instance);
			}
		}
	}
}

bool USROInventoryComponent::ReplicateSubobjects(UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (FSROInventoryEntry& Entry : InventoryList.Entries)
	{
		USROInventoryItemInstance* Instance = Entry.Instance;

		if (Instance && IsValid(Instance))
		{
			WroteSomething |= Channel->ReplicateSubobject(Instance, *Bunch, *RepFlags);
		}
	}

	return WroteSomething;
}

//////////////////////////////////////////////////////////////////////
//

// UCLASS(Abstract)
// class USROInventoryFilter : public UObject
// {
// public:
// 	virtual bool PassesFilter(USROInventoryItemInstance* Instance) const { return true; }
// };

// UCLASS()
// class USROInventoryFilter_HasTag : public USROInventoryFilter
// {
// public:
// 	virtual bool PassesFilter(USROInventoryItemInstance* Instance) const { return true; }
// };


