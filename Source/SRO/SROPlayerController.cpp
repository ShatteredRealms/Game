// Copyright 2022 Shattered Realms Online


#include "SROPlayerController.h"

#include "SROCharacter.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Save/SROSaveStatics.h"
#include "UI/SROHud.h"

ASROPlayerController::ASROPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer),
	CurrentTarget(nullptr),
	AttackTargetIndex(-1)
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
	ASROHud* SROHUD = Cast<ASROHud>(GetHUD());
	if (!SROHUD)
	{
		return Super::InputKey(Params);
	}

	ASROCharacter* SROCharacter = Cast<ASROCharacter>(GetCharacter());
	if (!SROCharacter)
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
		if (SROCharacter->GetFightingTarget())
		{
			SROCharacter->StopFighting();
			UpdateTargetingUI();
			return true;
		}
		
		if (CurrentTarget)
		{
			ClearTarget();
			return true;
		}
	}

	if (Params.Key == EKeys::LeftMouseButton
		&& Params.Event == IE_Released)
	{
		FHitResult Result;
		GetHitResultUnderCursor(ECC_WorldStatic, false, Result);
		AActor* Actor = Result.GetActor();
		if (ATarget* Target = Cast<ATarget>(Actor))
		{
			SetTarget(Target);
			return true;
		}
	}
	
	return Super::InputKey(Params);
}

void ASROPlayerController::CancelAction()
{
	if (!IsLocalController())
	{
		return;
	}
	
	if (CurrentTarget)
	{
		CurrentTarget->SetTargeted(false);
		return;
	}

	// Handle open inventory interfaces
}

void ASROPlayerController::NextAttackTarget()
{
	if (!GetCharacter())
	{
		return;
	}
	
	// @TODO(wil): Find way to cache this array and keep up to date
	TArray<AActor*> Targets;
	UGameplayStatics::GetAllActorsOfClass(this, AFightingTarget::StaticClass(), Targets);

	// Only target is self
	if (Targets.Num() == 1)
	{
		return;
	}

	// Only a single target
	if (Targets.Num() == 2)
	{
		if (Targets[0] != GetCharacter())
		{
			SetTarget(Cast<ATarget>(Targets[0]));
		}
		else
		{
			SetTarget(Cast<ATarget>(Targets[1]));
		}
		
		return;
	}
	
	Targets.Sort();

	// Check index validity
	if (AttackTargetIndex >= Targets.Num())
	{
		AttackTargetIndex = -1;
	}

	if (AttackTargetIndex == -1)
	{
		for (int idx = 0; idx < Targets.Num(); idx++)
		{
			if (CheckNextAttackTarget(Targets, idx))
			{
				return;
			}
		}
	}
	else
	{
		for (int idx = AttackTargetIndex + 1; idx != AttackTargetIndex; idx++)
		{
			if (idx >= Targets.Num())
			{
				idx = 0;
			}
			
			if (CheckNextAttackTarget(Targets, idx))
			{
				return;
			}
		}
	}

	if (AttackTargetIndex != -1
		&& CurrentTarget != Targets[AttackTargetIndex])
	{
		AttackTargetIndex = -1;
	}
}

bool ASROPlayerController::CheckNextAttackTarget(TArray<AActor*> Targets, const int Index)
{
	AFightingTarget* Target = Cast<AFightingTarget>(Targets[Index]);
	
	if (!Target
		|| Target == GetCharacter()
		|| GetCharacter()->GetDistanceTo(Target) > MaxNewTargetDistance)
	{
		return false;
	}
	
	FHitResult Result;
	GetCharacter()->ActorLineTraceSingle(Result, GetCharacter()->GetActorLocation(), Target->GetActorLocation(), ECC_Visibility, {});
	
	// if (Result.Component->GetAttachmentRoot() == Target->GetRootComponent())
	// {
		if (SetTarget(Target))
		{
			AttackTargetIndex = Index;
			return true;
		}
	// }

	return false;
}


void ASROPlayerController::UpdateTargetingUI()
{
	UpdateFightingTargetUI();

	if (!CurrentTarget)
	{
		ASROHud* HUD = GetHUD<ASROHud>();
		HUD->BaseUI->AttackTargetsWidget->SetAttackTarget(nullptr);
		return;
	}
	
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
	if (!HUD)
	{
		return;
	}

	auto SROCharacter = Cast<ASROCharacter>(GetCharacter());
	if (SROCharacter)
	{
		HUD->BaseUI->AttackTargetsWidget->SetFightingTarget(SROCharacter->GetFightingTarget());
	}
}

bool ASROPlayerController::SetTarget(ATarget* NewTarget)
{
	if (NewTarget == CurrentTarget
		|| (!IsLocalController() && GetLocalRole() != ROLE_Authority))
	{
		return false;
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

	if ((CurrentTarget && CurrentTarget->GetClass()->IsChildOf(AFightingTarget::StaticClass()))
		|| !CurrentTarget)
	{
		AttackTargetIndex = -1;
	}

	UpdateTargetingUI();
	CurrentTargetUpdated();
	return true;
}

void ASROPlayerController::StartAttack()
{
	if (!IsLocalController() && GetLocalRole() != ROLE_Authority)
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
	
	ASROCharacter* SROCharacter = Cast<ASROCharacter>(GetCharacter());
	if (!SROCharacter)
	{
		// @TODO(wil): Notify
		return;
	}

	if (SROCharacter->GetFightingTarget() == CastedCurrentTarget)
	{
		SROCharacter->StopFighting();
	}
	else
	{
		SROCharacter->StartFighting(CastedCurrentTarget);
	}
	
	UpdateFightingTargetUI();
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
	
	UpdateTargetingUI();
	FightTargetUpdated();
}

void ASROPlayerController::ClearTarget()
{
	CurrentTarget->SetTargeted(false);
	CurrentTarget = nullptr;
	AttackTargetIndex = -1;
	UpdateTargetingUI();
}
