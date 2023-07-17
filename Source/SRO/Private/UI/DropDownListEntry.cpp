// Copyright Shattered Realms Online All Rights Reserved


#include "UI/DropDownListEntry.h"

#include "SRO/SRO.h"

void UDropDownListEntry::NativeConstruct()
{
	Super::NativeConstruct();
	OriginalHoveredStyle = Button->WidgetStyle.Hovered;
	OriginalStyle = Button->WidgetStyle.Normal;
}

void UDropDownListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Data = Cast<UDropDownData>(ListItemObject);
	if (!Data)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to cast list item to drop down data"))
		return;
	}
	
	Button->OnClicked.AddDynamic(this, &UDropDownListEntry::OnClicked);
	Button->OnHovered.AddDynamic(this, &UDropDownListEntry::OnSelected);
	Button->OnUnhovered.AddDynamic(this, &UDropDownListEntry::OnUnhovered);
	Button->WidgetStyle.Normal = OriginalStyle;
}

void UDropDownListEntry::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);

	if (bIsSelected)
	{
		Button->WidgetStyle.Normal = OriginalHoveredStyle;
	}
	else
	{
		Button->WidgetStyle.Normal = OriginalStyle;
	}
}

void UDropDownListEntry::OnClicked()
{
	NativeOnItemSelectionChanged(true);
	Data->OnClicked.Broadcast(Data);
}

void UDropDownListEntry::OnSelected()
{
	NativeOnItemSelectionChanged(true);
	Data->OnSelected.Broadcast(Data);
	Data->bHovered = true;
}

void UDropDownListEntry::OnUnhovered()
{
	Data->bHovered = false;
}
