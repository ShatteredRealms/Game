// Copyright 2022 Shattered Realms Online


#include "SROPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Save/SROSaveStatics.h"

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
