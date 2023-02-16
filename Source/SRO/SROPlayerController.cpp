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
		UChatChannel* ChatChannel = NewObject<UChatChannel>();
		ChatChannel->Struct.Id = 1;
		ChatChannel->Struct.Name = "All";
		GetChatService()->ConnectToChannel(ChatChannel, AuthToken);
	}
}

USROChatService* ASROPlayerController::GetChatService()
{
	if (ChatService)
	{
		return ChatService;
	}
	
	ChatService = NewObject<USROChatService>();
	return ChatService;
}
