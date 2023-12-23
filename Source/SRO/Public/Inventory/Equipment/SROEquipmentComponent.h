// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SROEquipment.h"
#include "Gameplay/Abilities/SROAbilitySet.h"
#include "Net/Serialization/FastArraySerializer.h"

#include "SROEquipmentComponent.generated.h"

class UActorComponent;
class USROAbilitySystemComponent;
class USROEquipment;
class USROEquipmentInstance;
class USROEquipmentComponent;
class UObject;
struct FFrame;
struct FSROEquipmentList;
struct FNetDeltaSerializeInfo;
struct FReplicationFlags;

/** A single piece of applied equipment */
USTRUCT(BlueprintType)
struct FSROAppliedEquipmentEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FSROAppliedEquipmentEntry()
	{}

	FString GetDebugString() const;

private:
	friend FSROEquipmentList;
	friend USROEquipmentComponent;

	// The equipment class that got equipped
	UPROPERTY()
	TSubclassOf<USROEquipment> Equipment;

	UPROPERTY()
	TObjectPtr<USROEquipmentInstance> Instance = nullptr;

	// Authority-only list of granted handles
	UPROPERTY(NotReplicated)
	FSROAbilitySet_GrantedHandles GrantedHandles;
};

/** List of applied equipment */
USTRUCT(BlueprintType)
struct FSROEquipmentList : public FFastArraySerializer
{
	GENERATED_BODY()

	FSROEquipmentList()
		: OwnerComponent(nullptr)
	{
	}

	FSROEquipmentList(UActorComponent* InOwnerComponent)
		: OwnerComponent(InOwnerComponent)
	{
	}

public:
	//~FFastArraySerializer contract
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize);
	//~End of FFastArraySerializer contract

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FSROAppliedEquipmentEntry, FSROEquipmentList>(Entries, DeltaParms, *this);
	}

	USROEquipmentInstance* AddEntry(TSubclassOf<USROEquipment> EquipmentDefinition);
	void RemoveEntry(USROEquipmentInstance* Instance);

private:
	UAbilitySystemComponent* GetAbilitySystemComponent() const;

	friend USROEquipmentComponent;

private:
	// Replicated list of equipment entries
	UPROPERTY()
	TArray<FSROAppliedEquipmentEntry> Entries;

	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;
};

template<>
struct TStructOpsTypeTraits<FSROEquipmentList> : public TStructOpsTypeTraitsBase2<FSROEquipmentList>
{
	enum { WithNetDeltaSerializer = true };
};


/**
 * Manages equipment applied to a pawn
 */
UCLASS(BlueprintType, Const)
class USROEquipmentComponent : public UActorComponent 
{
	GENERATED_BODY()

public:
	USROEquipmentComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	USROEquipmentInstance* EquipItem(TSubclassOf<USROEquipment> EquipmentDefinition);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void UnequipItem(USROEquipmentInstance* ItemInstance);

	//~UObject interface
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	//~End of UObject interface

	//~UActorComponent interface
	//virtual void EndPlay() override;
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	virtual void ReadyForReplication() override;
	//~End of UActorComponent interface

	/** Returns the first equipped instance of a given type, or nullptr if none are found */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	USROEquipmentInstance* GetFirstInstanceOfType(TSubclassOf<USROEquipmentInstance> InstanceType);

 	/** Returns all equipped instances of a given type, or an empty array if none are found */
 	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<USROEquipmentInstance*> GetEquipmentInstancesOfType(TSubclassOf<USROEquipmentInstance> InstanceType) const;

	/** Returns the equipped instance of the given slot, or nullptr if nothing is equipped in that slot */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TSubclassOf<USROEquipment> GetEquipmentInSlot(ESROEquipmentSlot Slot) const;

	template <typename T>
	T* GetFirstInstanceOfType()
	{
		return (T*)GetFirstInstanceOfType(T::StaticClass());
	}

private:
	UPROPERTY(Replicated)
	FSROEquipmentList EquipmentList;
};
