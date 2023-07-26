// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Targeting/TargetDetailsWidget.h"

#include "GameFramework/FightingTarget.h"

void UTargetDetailsWidget::Setup(ATarget* NewTarget)
{
	Target = NewTarget;
	if (!Target)
	{
		return;
	}

	SetVisibility(ESlateVisibility::Visible);

	UpdateTargetName();

	if (AFightingTarget* FightingTarget = Cast<AFightingTarget>(Target))
	{
		HealthBar->SetVisibility(ESlateVisibility::Visible);
		UpdateHealthBarSize();
		UpdateHealthPercentage();
	}

	// @TODO(wil): Set faction information if it's a player character
}

void UTargetDetailsWidget::UpdateHealthBarSize()
{
	if (AFightingTarget* FightingTarget = Cast<AFightingTarget>(Target))
	{
		HealthSizeBox->SetWidthOverride(200 + FMath::Log2(FightingTarget->GetMaxHealth()) * 10);
	}
}

void UTargetDetailsWidget::UpdateHealthPercentage()
{
	if (AFightingTarget* FightingTarget = Cast<AFightingTarget>(Target))
	{
		HealthBar->SetPercent(FightingTarget->GetCurrentHealth() / FightingTarget->GetMaxHealth());
	}
}

void UTargetDetailsWidget::UpdateTargetName()
{
	if (Target)
	{
		TargetNameText->SetText(FText::FromString(Target->GetDisplayName()));
	}
}

void UTargetDetailsWidget::SetTargeted_Implementation(bool bNewTargeted)
{
	bTargeted = bNewTargeted;
	
	if (bFightingTargeted)
	{
		return;
	}

	if (bTargeted)
	{
			Border->SetBrushColor(FLinearColor{255, 255, 255, 1});
	}
	else
	{
			Border->SetBrushColor(FLinearColor{255, 255, 255, 0});
	}
}

void UTargetDetailsWidget::SetFightingTarget_Implementation(bool bNewFightingTargeted)
{
	bFightingTargeted = bNewFightingTargeted;
	if (bFightingTargeted)
	{
		Border->SetBrushColor(FLinearColor{255, 0, 0, 1});
	}
	else
	{
		if (bTargeted)
		{
			Border->SetBrushColor(FLinearColor{255, 255, 255, 1});
		}
		else
		{
			Border->SetBrushColor(FLinearColor{255, 255, 255, 0});
		}
	}
}
