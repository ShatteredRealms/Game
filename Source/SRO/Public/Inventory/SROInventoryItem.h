// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "SROInventoryItem.generated.h"

class USROInventoryItemInstance;

//////////////////////////////////////////////////////////////////////

// Represents a fragment of an item definition
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class SRO_API USROInventoryItemFragment : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnInstanceCreated(USROInventoryItemInstance* Instance) const {}
};

UENUM(BlueprintType)
enum EItemQuality
{
	Common,
	Rare,
	Epic,
	Legendary,
};

/**
 * Represents a base inventory item
 */
UCLASS(Blueprintable, Const, Abstract)
class SRO_API USROInventoryItem : public UObject
{
	GENERATED_BODY()

public:
	USROInventoryItem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	 * Fragments for the item
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Display, Instanced)
	TArray<TObjectPtr<USROInventoryItemFragment>> Fragments;

	/**
	 * Display name for the item
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory|Item")
	FText DisplayName;
	
	/**
	 * Max stack size for the item.
	 * if <= 1, then the item is not stackable
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory|Item")
	int32 MaxStackCount;

	/**
	 * Min level of the item
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory|Item")
	int32 MinLevel;

	/**
	 * Max level of the item
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory|Item")
	int32 MaxLevel;

	/**
	 * Skeletal mesh for the item. It can safely be null.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Item")
	TObjectPtr<USkeletalMesh> SkeletalMesh;

	/**
	 * Icon brush for the item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Item")
	FSlateBrush IconBrush;
	
	/**
	 * Whether the item can stack
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory|Item")
	FORCEINLINE bool CanStack() const { return MaxStackCount > 1; }

public:
	const USROInventoryItemFragment* FindFragmentByClass(TSubclassOf<USROInventoryItemFragment> FragmentClass) const;

	template <typename ResultClass>
	const ResultClass* FindFragmentByClass() const
	{
		return (ResultClass*)FindFragmentByClass(ResultClass::StaticClass());
	}
};
