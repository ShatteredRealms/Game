// Copyright 2022 Shattered Realms Online


#include "SROPlayerController.h"

#include "SRO.h"
#include "SROCharacter.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Save/SROSaveStatics.h"
#include "UI/SROHud.h"

ASROPlayerController::ASROPlayerController() : Super()
{
	bEnableClickEvents = true;
}

void ASROPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI mode = FInputModeGameAndUI();
	mode.SetHideCursorDuringCapture(true);
	mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	SetShowMouseCursor(true);
	SetInputMode(mode);
}

void ASROPlayerController::PreDisconnect()
{
	if (IsLocalController())
	{
		USROSaveStatics::SaveGame(this);
	}
}

bool ASROPlayerController::InputKey(const FInputKeyParams& Params)
{
	if (Params.Key != EKeys::Enter)
	{
		return Super::InputKey(Params);
	}
	
	ASROHud* SROHUD = Cast<ASROHud>(GetHUD());
	if (!SROHUD)
	{
		return Super::InputKey(Params);
	}
	
	if (
		Params.Key == EKeys::Enter &&
		Params.Event == IE_Pressed &&
		SROHUD->BaseUI->PrevFocusedChatTab)
	{
		SROHUD->BaseUI->PrevFocusedChatTab->ChatTextBox->SetFocus();
		return true;
	}

	if (Params.Key == EKeys::Escape && Params.Event == IE_Pressed)
	{
		if (CurrentTarget)
		{
			ClearTarget();
			return true;
		}
	}
	
	return Super::InputKey(Params);
}

void ASROPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ASROCharacter* SROCharacter = Cast<ASROCharacter>(InPawn);
	if (SROCharacter)
	{
		SROCharacter->OnFightingTargetChanged().AddUObject(this, &ASROPlayerController::UpdateFightingTargetUI);
	}
}

void ASROPlayerController::UpdateTargetUI()
{
	if (CurrentTarget->GetClass()->IsChildOf(AFightingTarget::StaticClass()))
	{
		UpdateAttackTargetUI();
	}
}

void ASROPlayerController::UpdateAttackTargetUI()
{
	if (!IsLocalController())
	{
		return;
	}
	
	const auto CastedCurrentTarget = Cast<AFightingTarget>(CurrentTarget);
	if (!CastedCurrentTarget)
	{
		return;
	}
	
	ASROHud* HUD = GetHUD<ASROHud>();
	HUD->BaseUI->AttackTargetsWidget->SetAttackTarget(CastedCurrentTarget);
}

void ASROPlayerController::UpdateFightingTargetUI()
{
	if (!IsLocalController())
	{
		return;
	}
	
	ASROHud* HUD = GetHUD<ASROHud>();

	auto SROCharacter = Cast<ASROCharacter>(GetCharacter());
	if (SROCharacter)
	{
		HUD->BaseUI->AttackTargetsWidget->SetFightingTarget(SROCharacter->GetFightingTarget());
	}
}

void ASROPlayerController::SetTarget(ATarget* NewTarget)
{
	if (!IsLocalController()
		&& GetLocalRole() != ROLE_Authority
		&& NewTarget == CurrentTarget)
	{
		return;
	}
	
	if (CurrentTarget)
	{
		CurrentTarget->SetTargeted(false);
	}

	CurrentTarget = NewTarget;
	if (CurrentTarget)
	{
		CurrentTarget->SetTargeted(true);
	}

	UpdateTargetUI();
	CurrentTargetUpdated();
}

void ASROPlayerController::StartAttack()
{
	if (!IsLocalController() || GetLocalRole() != ROLE_Authority)
	{
		return;
	}
	
	if (!CurrentTarget)
	{
		// @TODO(wil): Notify no target
		return;
	}

	const auto CastedCurrentTarget = Cast<AFightingTarget>(CurrentTarget);
	if (!CastedCurrentTarget)
	{
		// @TODO(wil): Notify can't fight the target
		return;
	}
	
	auto SROCharacter = Cast<ASROCharacter>(GetCharacter());
	if (SROCharacter)
	{
		// @TODO(wil): Notify
		return;
	}

	SROCharacter->StartFighting(CastedCurrentTarget);
	CurrentTarget = nullptr;
	UpdateAttackTargetUI();
}

void ASROPlayerController::EndAttack()
{
	if (!IsLocalController()
		&& GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	auto SROCharacter = Cast<ASROCharacter>(GetCharacter());
	if (SROCharacter)
	{
		SROCharacter->StopFighting();
	}
	
	UpdateFightingTargetUI();
	FightTargetUpdated();
}

void ASROPlayerController::ClearTarget()
{
	CurrentTarget->SetTargeted(false);
	CurrentTarget = nullptr;
	
	ASROHud* HUD = GetHUD<ASROHud>();
	HUD->BaseUI->AttackTargetsWidget->SetAttackTarget(nullptr);
}
