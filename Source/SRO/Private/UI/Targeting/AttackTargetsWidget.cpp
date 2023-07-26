// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Targeting/AttackTargetsWidget.h"

void UAttackTargetsWidget::SetAttackTarget(AFightingTarget* NewTarget)
{
	AttackTargetWidget->SetTarget(NewTarget);
	if (AttackTargetWidget->GetTarget() == FightingTargetWidget->GetTarget())
	{
		AttackTargetWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UAttackTargetsWidget::SetFightingTarget(AFightingTarget* NewTarget)
{
	FightingTargetWidget->SetTarget(NewTarget);
}
