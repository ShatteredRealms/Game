// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "Net/Serialization/FastArraySerializer.h"

#include "SROInventoryComponent.generated.h"

class USROInventoryItem;
class USROInventoryItemInstance;
class USROInventoryComponent;
class UObject;
struct FFrame;
struct FSROInventoryList;
struct FNetDeltaSerializeInfo;
struct FReplicationFlags;

/** A message when an item is added to the inventory */
USTRUCT(BlueprintType)
struct FSROInventoryChangeMessage
{
	GENERATED_BODY()

	//@TODO: Tag based names+owning actors for inventories instead of directly exposing the component?
	UPROPERTY(BlueprintReadOnly, Category=Inventory)
	TObjectPtr<UActorComponent> InventoryOwner = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	TObjectPtr<USROInventoryItemInstance> Instance = nullptr;

	UPROPERTY(BlueprintReadOnly, Category=Inventory)
	int32 NewCount = 0;

	UPROPERTY(BlueprintReadOnly, Category=Inventory)
	int32 Delta = 0;
};

/** A single entry in an inventory */
USTRUCT(BlueprintType)
struct FSROInventoryEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FSROInventoryEntry()
	{}

	FString GetDebugString() const;

private:
	friend FSROInventoryList;
	friend USROInventoryComponent;

	UPROPERTY()
	TObjectPtr<USROInventoryItemInstance> Instance = nullptr;

	UPROPERTY()
	int32 StackCount = 0;

	UPROPERTY(NotReplicated)
	int32 LastObservedCount = INDEX_NONE;
};

/** List of inventory items */
USTRUCT(BlueprintType)
struct FSROInventoryList : public FFastArraySerializer
{
	GENERATED_BODY()

	FSROInventoryList()
		: OwnerComponent(nullptr)
	{
	}

	FSROInventoryList(UActorComponent* InOwnerComponent)
		: OwnerComponent(InOwnerComponent)
	{
	}

	TArray<USROInventoryItemInstance*> GetAllItems() const;

public:
	//~FFastArraySerializer contract
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize);
	//~End of FFastArraySerializer contract

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FSROInventoryEntry, FSROInventoryList>(Entries, DeltaParms, *this);
	}

	USROInventoryItemInstance* AddEntry(TSubclassOf<USROInventoryItem> ItemClass, int32 StackCount);
	void AddEntry(USROInventoryItemInstance* Instance);

	void RemoveEntry(USROInventoryItemInstance* Instance);

private:
	void BroadcastChangeMessage(FSROInventoryEntry& Entry, int32 OldCount, int32 NewCount);

private:
	friend USROInventoryComponent;

private:
	// Replicated list of items
	UPROPERTY()
	TArray<FSROInventoryEntry> Entries;

	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;
};

template<>
struct TStructOpsTypeTraits<FSROInventoryList> : public TStructOpsTypeTraitsBase2<FSROInventoryList>
{
	enum { WithNetDeltaSerializer = true };
};


/**
 * Manages an inventory
 */
UCLASS(BlueprintType)
class SRO_API USROInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USROInventoryComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	bool CanAddItem(TSubclassOf<USROInventoryItem> ItemDef, int32 StackCount = 1);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	USROInventoryItemInstance* AddItem(TSubclassOf<USROInventoryItem> ItemDef, int32 StackCount = 1);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	void AddItemInstance(USROInventoryItemInstance* ItemInstance);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	void RemoveItemInstance(USROInventoryItemInstance* ItemInstance);

	UFUNCTION(BlueprintCallable, Category=Inventory, BlueprintPure=false)
	TArray<USROInventoryItemInstance*> GetAllItems() const;

	UFUNCTION(BlueprintCallable, Category=Inventory, BlueprintPure)
	USROInventoryItemInstance* FindFirstItemStackBy(TSubclassOf<USROInventoryItem> ItemDef) const;

	int32 GetTotalItemCountBy(TSubclassOf<USROInventoryItem> ItemDef) const;
	bool ConsumeItemsBy(TSubclassOf<USROInventoryItem> ItemDef, int32 NumToConsume);

	//~UObject interface
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	virtual void ReadyForReplication() override;
	//~End of UObject interface

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	uint8 InventorySize;
	
private:
	friend class USROInventoryWidget;
	
	UPROPERTY(Replicated)
	FSROInventoryList InventoryList;
};
