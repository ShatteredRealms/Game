// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Inventory/SROInventoryItemInstance.h"
#include "SROInventoryItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API USROInventoryItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private:
	UPROPERTY()
	USROInventoryItemInstance* ItemInstance;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UImage* ItemImage;

	/** Sets the current item instance and returns the old ItemInstance. */
	USROInventoryItemInstance* SetItemInstance(USROInventoryItemInstance* NewItemInstance);
	
public:

	/** Get the item instance for this item */
	FORCEINLINE USROInventoryItemInstance* GetItemInstance() const { return ItemInstance; }

	/** Update the item image based on the current item instance. If it's null, then make it invisible. */
	void UpdateVisuals();

	//~IUserObjectListEntry interface
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	//~End of IUserObjectListEntry interface
};
