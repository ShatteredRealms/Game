// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SROInventoryItem.h"
#include "SROInventoryItemInstance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SRO_API USROInventoryItemInstance : public UObject
{
	GENERATED_BODY()
	
private:
	friend struct FSROInventoryList;
	
	UPROPERTY(Replicated)
	TSubclassOf<USROInventoryItem> BaseItem;
	
	UPROPERTY(Replicated)
	int32 StackCount = 1;

	FORCEINLINE void SetItem(TSubclassOf<USROInventoryItem> NewBaseItem) { BaseItem = NewBaseItem; }

public:
	virtual bool IsSupportedForNetworking() const override { return true; };

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category=Inventory)
	FORCEINLINE TSubclassOf<USROInventoryItem> GetItem() const { return BaseItem; }

	UFUNCTION(BlueprintCallable, Category=Inventory)
	FORCEINLINE USROInventoryItem* GetItemCDO() const { return BaseItem->GetDefaultObject<USROInventoryItem>(); }

	template <typename ResultClass>
	FORCEINLINE ResultClass* GetItemCDO() const { return BaseItem->GetDefaultObject<ResultClass>(); }

	template <typename ResultClass>
	const ResultClass* FindFragmentByClass() const
	{
		return (ResultClass*)FindFragmentByClass(ResultClass::StaticClass());
	}
};
