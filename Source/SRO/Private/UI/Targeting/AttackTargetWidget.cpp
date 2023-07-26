// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Targeting/AttackTargetWidget.h"

void UAttackTargetWidget::SetTarget(AFightingTarget* NewTarget)
{
	Target = NewTarget;
	
	if (Target)
	{
		TargetNameText->SetText(FText::FromString(Target->GetDisplayName()));
		SetVisibility(ESlateVisibility::Visible);
		TargetUpdated();
		return;
	}

	SetVisibility(ESlateVisibility::Collapsed);
}
