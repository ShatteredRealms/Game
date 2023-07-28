// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Combat/VerticalProgressWidget.h"

void UVerticalProgressWidget::NativePreConstruct()
{
	Super::NativeConstruct();
	ProgressBar->SetFillColorAndOpacity(FillColor);
}

void UVerticalProgressWidget::SetFillPercent(float NewPercent)
{
	ProgressBar->SetPercent(NewPercent);
}
