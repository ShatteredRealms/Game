// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SROInventoryItemWidget.h"
#include "Inventory/SROInventoryComponent.h"
#include "UI/DraggableResizableBaseWindow.h"
#include "SROInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API USROInventoryWidget : public UDraggableResizableBaseWindow
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USROInventoryItemWidget> ItemWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<USROInventoryItemWidget*> InventorySlots;

public:
	virtual void NativeConstruct() override;

	FORCEINLINE uint8 GetInventorySize() const { return InventorySlots.Num(); }
	FORCEINLINE uint8 GetInventoryMaxSize() const { return GetInventoryComponent()->InventorySize; }

	UFUNCTION(BlueprintCallable)
	bool AddItem(USROInventoryItemInstance* ItemInstance, int32 ItemSlot = -1);
	
private:
	USROInventoryComponent* GetInventoryComponent() const;
};
