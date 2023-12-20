// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Inventory/SROInventoryWidget.h"

#include "SROPlayerController.h"
#include "Gameplay/Character/SROCharacter.h"

bool USROInventoryWidget::AddItem(USROInventoryItemInstance* ItemInstance, int32 ItemSlot)
{
	if (ItemSlot < 0)
	{
		
	}

	return true;
}

USROInventoryComponent* USROInventoryWidget::GetInventoryComponent() const
{
	ASROPlayerController* PC = GetOwningPlayer<ASROPlayerController>();
	check(PC);

	ASROCharacter* Character = PC->GetPawn<ASROCharacter>();
	check(Character);

	return Character->GetInventoryComponent();
}

void USROInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const uint8 MaxSize = GetInventoryMaxSize();
	InventorySlots.Empty();
	InventorySlots.SetNum(MaxSize, false);
	for (int idx = 0; idx < MaxSize; ++idx)
	{
		InventorySlots[idx] = CreateWidget<USROInventoryItemWidget>(GetOwningPlayer(), ItemWidgetClass);
	}
}
