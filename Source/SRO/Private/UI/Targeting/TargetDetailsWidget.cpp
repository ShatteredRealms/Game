// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Targeting/TargetDetailsWidget.h"
#include "Gameplay/Character/FightingCharacter.h"

void UTargetDetailsWidget::Setup(AActor* NewTarget)
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
	
	Target = NewTarget;

	if (AFightingCharacter* Character = Cast<AFightingCharacter>(Target))
	{
		HealthBar->SetVisibility(ESlateVisibility::Visible);
		SetDisplayName(Character->GetDisplayName());
		UpdateHealthBarSize(Character->GetMaxHealth());
		UpdateHealthPercentage(Character->GetHealth(), Character->GetMaxHealth());
		UpdateHealthBarSize(100);
		UpdateHealthPercentage(100, 100);
	}
	else
	{
		HealthBar->SetVisibility(ESlateVisibility::Collapsed);
		SetDisplayName(NewTarget->GetName());
	}

	// @TODO(wil): Set faction information if it's a player character
	FactionNameText->SetVisibility(ESlateVisibility::Collapsed);
}

void UTargetDetailsWidget::SetDisplayName(FString NewDisplayName)
{
	TargetNameText->SetText(FText::FromString(NewDisplayName));
}

void UTargetDetailsWidget::UpdateHealthBarSize(float MaxHealth)
{
	HealthSizeBox->SetWidthOverride(200 + FMath::Log2(MaxHealth) * 10);
}

void UTargetDetailsWidget::UpdateHealthPercentage(float CurrentHealth, float MaxHealth)
{
	HealthBar->SetPercent(CurrentHealth / MaxHealth);
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

void UTargetDetailsWidget::SetAttacked_Implementation(bool bNewFightingTargeted)
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
