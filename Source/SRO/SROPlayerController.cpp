// Copyright 2022 Shattered Realms Online


#include "SROPlayerController.h"

#include "Gameplay/Character/SROCharacter.h"
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
	mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
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
		if (Actor->GetClass()->ImplementsInterface(UTargetable::StaticClass()))
		{
			SetTarget(Actor);
			return true;
		}
	}

	if (Params.Key == EKeys::T
		&& Params.Event == IE_Pressed)
	{
		SROCharacter->GetTargetingComponent()->Setup(SROCharacter);
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
		ITargetable* TargetableActor = Cast<ITargetable>(CurrentTarget);
		TargetableActor->GetTargetingComponent()->SetTargeted(false);
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
	UGameplayStatics::GetAllActorsOfClass(this, AFightingCharacter::StaticClass(), Targets);

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
			SetTarget(Targets[0]);
		}
		else
		{
			SetTarget(Targets[1]);
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
	AFightingCharacter* Target = Cast<AFightingCharacter>(Targets[Index]);
	
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
	
	UpdateAttackTargetUI();
}

void ASROPlayerController::UpdateAttackTargetUI()
{
	if (!IsLocalController())
	{
		return;
	}
	
	const auto CastedCurrentTarget = Cast<AFightingCharacter>(CurrentTarget);
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

void ASROPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	SetupUIForControlledPawn();
}

void ASROPlayerController::OnUnPossess()
{
	if (GetPawn())
	{
		GetPawn()->OnTakeAnyDamage.RemoveDynamic(this, &ASROPlayerController::ControlledPawnTookDamage);
	}
	
	Super::OnUnPossess();
}

void ASROPlayerController::ControlledPawnTookDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamagedActor != GetPawn())
	{
		DamagedActor->OnTakeAnyDamage.RemoveDynamic(this, &ASROPlayerController::ControlledPawnTookDamage);
		return;
	}
	
	ASROHud* SROHUD = GetHUD<ASROHud>();
	if (!SROHUD)
	{
		return;
	}
	
	AFightingCharacter* FightingTarget = Cast<AFightingCharacter>(DamagedActor);
	if (!FightingTarget)
	{
		return;
	}
	SROHUD->BaseUI->HealthBar->SetFillPercent(FightingTarget->GetHealth() / FightingTarget->GetMaxHealth());
}

void ASROPlayerController::SetupUIForControlledPawn()
{
	if (!GetPawn())
	{
		return;
	}
	
	ASROHud* SROHUD = GetHUD<ASROHud>();
	if (!SROHUD)
	{
		return;
	}
	
	GetPawn()->OnTakeAnyDamage.AddDynamic(this, &ASROPlayerController::ControlledPawnTookDamage);
	
	AFightingCharacter* FightingTarget = Cast<AFightingCharacter>(GetPawn());
	if (FightingTarget)
	{
		SROHUD->BaseUI->HealthBar->SetFillPercent(FightingTarget->GetHealth() / FightingTarget->GetMaxHealth());
	}

	
}

bool ASROPlayerController::SetTarget(AActor* NewTarget)
{
	if (NewTarget == CurrentTarget
		|| (!IsLocalController() && GetLocalRole() != ROLE_Authority))
	{
		return false;
	}
	
	if (CurrentTarget)
	{
		if (ITargetable* CastedTarget = Cast<ITargetable>(CurrentTarget))
		{
			if (CastedTarget->GetTargetingComponent())
			{
				CastedTarget->GetTargetingComponent()->SetTargeted(false);
			}
		}
	}

	CurrentTarget = NewTarget;
	if (CurrentTarget)
	{
		if (ITargetable* CastedTarget = Cast<ITargetable>(CurrentTarget))
		{
			if (CastedTarget->GetTargetingComponent())
			{
				CastedTarget->GetTargetingComponent()->SetTargeted(true);
			}
		}
	}

	if ((CurrentTarget && !CurrentTarget->GetClass()->IsChildOf(AFightingCharacter::StaticClass()))
		|| !CurrentTarget)
	{
		AttackTargetIndex = -1;
	}

	UpdateAttackTargetUI();
	CurrentTargetUpdated();
	return true;
}

void ASROPlayerController::StartAttack()
{
	if (!IsLocalController() && GetLocalRole() != ROLE_Authority)
	{
		return;
	}
	
	if (CurrentTarget == nullptr)
	{
		// @TODO(wil): Notify no target
		return;
	}

	const auto CastedCurrentTarget = Cast<AFightingCharacter>(CurrentTarget);
	if (CastedCurrentTarget == nullptr)
	{
		// @TODO(wil): Notify can't fight the target
		return;
	}
	
	ASROCharacter* SROCharacter = Cast<ASROCharacter>(GetCharacter());
	if (SROCharacter == nullptr)
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
	if (ITargetable* CastedTarget = Cast<ITargetable>(CurrentTarget))
	{
		CastedTarget->GetTargetingComponent()->SetTargeted(false);
	}
	CurrentTarget = nullptr;
	AttackTargetIndex = -1;
	UpdateTargetingUI();
}
