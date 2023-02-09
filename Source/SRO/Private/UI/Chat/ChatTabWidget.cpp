// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Chat/ChatTabWidget.h"

void UChatTabWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TabButton->OnClicked.AddDynamic(this, &UChatTabWidget::OnTabClicked);
}

void UChatTabWidget::OnTabClicked()
{
	OnChatTabSelected->Execute(this);
}
