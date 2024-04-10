// Copyright Shattered Realms Online All Rights Reserved


#include "UI/DropDownList.h"

#include "SRO/SRO.h"


UDropDownList::UDropDownList(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SetIsFocusable(true);
}

UDropDownData* UDropDownList::CreateEntry(FString Name)
{
	auto Data = NewObject<UDropDownData>();
	Data->Name = Name;
	return AddEntry(Data);
}

UDropDownData* UDropDownList::AddEntry(UDropDownData* Data)
{
	Entries->AddItem(Data);
	Data->OnSelected.AddDynamic(this, &UDropDownList::OnDropDownHovered);

	if (Entries->GetNumItems() == 1)
	{
		Entries->SetSelectedIndex(0);
		SetVisibility(ESlateVisibility::Visible);
	}
	
	return Data;
}

void UDropDownList::SelectNext()
{
	Entries->SetSelectedIndex((GetSelectedIndex() + 1) % Entries->GetNumItems());
}

void UDropDownList::SelectPrevious()
{
	auto NextIdx = GetSelectedIndex() - 1;
	if (NextIdx < 0)
	{
		NextIdx = Entries->GetNumItems() - 1;
	}
	Entries->SetSelectedIndex(NextIdx);
}

void UDropDownList::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);

	if (!(InFocusEvent.GetCause() == EFocusCause::Mouse && AnyButtonsHovered()))
	{
		Clear();
	}
}

FReply UDropDownList::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Up ||
		(InKeyEvent.GetKey() == EKeys::Tab && InKeyEvent.IsShiftDown()))
	{
		SelectPrevious();
		return FReply::Handled();
	}

	if (InKeyEvent.GetKey() == EKeys::Down ||
		InKeyEvent.GetKey() == EKeys::Tab)
	{
		SelectNext();
		return FReply::Handled();
	}

	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		GetParent()->SetFocus();
		return FReply::Handled();
	}

	if (InKeyEvent.GetKey() == EKeys::Enter)
	{
		const auto Entry = Entries->GetSelectedItem<UDropDownData>();
		if (Entry)
		{
			Entry->OnClicked.Broadcast(Entry);
			Clear();
		}
		return FReply::Handled();
	}
	
	return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
}

void UDropDownList::Clear()
{
	for (auto Data : Entries->GetListItems())
	{
		Data->ConditionalBeginDestroy();
	}

	Entries->ClearListItems();
	SetVisibility(ESlateVisibility::Collapsed);
}

void UDropDownList::OnDropDownHovered(UDropDownData* SelectedData)
{
	Entries->SetSelectedItem(SelectedData);
}

int32 UDropDownList::GetSelectedIndex()
{
	const auto Data = Entries->GetSelectedItem<UDropDownData>();
	if (!Data)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get selected item"))
		return -1;
	}
	
	return Entries->GetIndexForItem(Data);
}

bool UDropDownList::AnyButtonsHovered()
{
	for (const auto ListItem : Entries->GetListItems())
	{
		const auto Data = Cast<UDropDownData>(ListItem);
		if (Data && Data->bHovered)
		{
			return true;
		}
	}
	return false;
}
