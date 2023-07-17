// Copyright Shattered Realms Online All Rights Reserved


#include "UI/TabWidget.h"

void UTabWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TabButton->OnClicked.AddDynamic(this, &UTabWidget::OnTabClicked);
}

void UTabWidget::SetSelected(bool bNewSelection)
{
	bSelected = bNewSelection;
	if (bSelected)
	{
		TabButton->SetStyle(ActiveStyle);
	}
	else
	{
		TabButton->SetStyle(InactiveStyle);
	}
}

void UTabWidget::OnTabClicked()
{
	OnTabSelected->Execute(this);
}
