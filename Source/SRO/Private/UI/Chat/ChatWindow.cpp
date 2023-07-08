// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Chat/ChatWindow.h"

void UChatWindow::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->SetVisibility(ESlateVisibility::Hidden);
}
