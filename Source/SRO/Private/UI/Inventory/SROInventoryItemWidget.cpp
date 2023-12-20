// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Inventory/SROInventoryItemWidget.h"

USROInventoryItemInstance* USROInventoryItemWidget::SetItemInstance(USROInventoryItemInstance* NewItemInstance)
{
	USROInventoryItemInstance* PrevItemInstance = ItemInstance;
	ItemInstance = NewItemInstance;
	
	UpdateVisuals();
	
	return PrevItemInstance;
}

void USROInventoryItemWidget::UpdateVisuals()
{
	if (ItemInstance)
	{
		ItemImage->SetBrush(ItemInstance->GetItemCDO()->IconBrush);
		
		return;
	}

	FSlateBrush Brush = FSlateBrush{};
	Brush.TintColor = FSlateColor{FLinearColor{0, 0, 0, 0}};
	ItemImage->SetBrush(Brush);
}

void USROInventoryItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	SetItemInstance(Cast<USROInventoryItemInstance>(ListItemObject));
}

void USROInventoryItemWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}
