// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Targeting/AttackTargetsWidget.h"

void UAttackTargetsWidget::SetAttackTarget(AFightingTarget* NewTarget)
{
	AttackTargetWidget->SetTarget(NewTarget);
}

void UAttackTargetsWidget::SetFightingTarget(AFightingTarget* NewTarget)
{
	FightingTargetWidget->SetTarget(NewTarget);
}
