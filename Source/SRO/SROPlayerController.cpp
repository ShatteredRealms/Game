// Copyright 2022 Shattered Realms Online


#include "SROPlayerController.h"

void ASROPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI mode = FInputModeGameAndUI();
	mode.SetHideCursorDuringCapture(false);
	mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	
	SetInputMode(mode);
}
