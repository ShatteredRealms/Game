// Copyright 2022 Shattered Realms Online


#include "SROPlayerController.h"

#include "SROGameMode.h"
#include "Net/UnrealNetwork.h"

void ASROPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI mode = FInputModeGameAndUI();
	mode.SetHideCursorDuringCapture(true);
	mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	SetShowMouseCursor(true);
	SetInputMode(mode);

	if (IsLocalPlayerController())
	{
		ChatService = NewObject<USROChatService>();
		ChatService->ConnectToChannel(1, AuthToken);
	}
}
