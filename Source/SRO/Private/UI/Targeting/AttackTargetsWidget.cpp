// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Targeting/AttackTargetsWidget.h"

void UAttackTargetsWidget::SetAttackTarget(AFightingCharacter* NewTarget)
{
	AttackTargetWidget->SetTarget(NewTarget);
	if (AttackTargetWidget->GetTarget() == FightingTargetWidget->GetTarget())
	{
		AttackTargetWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		AttackTargetWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UAttackTargetsWidget::SetFightingTarget(AFightingCharacter* NewTarget)
{
	FightingTargetWidget->SetTarget(NewTarget);
}
