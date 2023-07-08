// Copyright Shattered Realms Online All Rights Reserved


#include "UI/DraggableResizableBaseWindow.h"

#include "Components/NamedSlot.h"
#include "SRO/SRO.h"

UDraggableResizableBaseWindow::UDraggableResizableBaseWindow()
{
	static ConstructorHelpers::FClassFinder<UTabWidget> FoundTabWidget(TEXT("/Game/SRO/Core/UI/BP_Tab"));
	TabWidgetClass = FoundTabWidget.Class;
}

void UDraggableResizableBaseWindow::NativeConstruct()
{
	Super::NativeConstruct();

	OnTabSelected.BindUObject(this, &UDraggableResizableBaseWindow::FocusTab);
}

UTabWidget* UDraggableResizableBaseWindow::CreateTab(const FText& TabName, UUserWidget* Content)
{
	UTabWidget* Tab = CreateWidget<UTabWidget>(GetOwningPlayer(), TabWidgetClass);

	if (!Tab)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to create tab"));
		return nullptr;
	}
	
	Tab->TabName->SetText(TabName);
	Tab->OnTabSelected = &OnTabSelected;
	Tabs->AddChildToHorizontalBox(Tab);
	TabMapping.Add(Tab, Content);

	ContentSlot->AddChild(Content);
	Content->SetVisibility(ESlateVisibility::Hidden);

	if (!ActiveTab)
	{
		FocusTab(Tab);
	}

	return Tab;
}

void UDraggableResizableBaseWindow::AppendTab(UTabWidget* Tab, UUserWidget* Content)
{
	Tabs->AddChildToHorizontalBox(Tab);
	TabMapping.Add(Tab, Content);
}

void UDraggableResizableBaseWindow::FocusTab(UTabWidget* Tab)
{
	for (const TPair<UTabWidget*, UUserWidget*>& tab : TabMapping)
	{
		if (tab.Key == Tab)
		{
			Tab->SetSelected(true);
			ActiveTab = tab.Key;
			tab.Value->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			tab.Key->SetSelected(false);
			tab.Value->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UDraggableResizableBaseWindow::SetCloseable(bool IsCloseable)
{
	CloseButton->SetVisibility(IsCloseable ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
