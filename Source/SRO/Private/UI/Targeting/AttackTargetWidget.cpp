// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Targeting/AttackTargetWidget.h"

void UAttackTargetWidget::SetTarget(AFightingTarget* NewTarget)
{
	if (NewTarget)
	{
		TargetNameText->SetText(FText::FromString(NewTarget->GetDisplayName()));
		Target = NewTarget;
		SetVisibility(ESlateVisibility::Visible);
		return;
	}

	SetVisibility(ESlateVisibility::Collapsed);
}
