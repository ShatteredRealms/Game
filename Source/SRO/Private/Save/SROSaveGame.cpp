// Copyright Shattered Realms Online All Rights Reserved


#include "Save/SROSaveGame.h"

#include "Kismet/GameplayStatics.h"

USROSaveGame* USROSaveGame::CreateDefault()
{
	USaveGame* BaseSaveGame = UGameplayStatics::CreateSaveGameObject(StaticClass());
	if (!BaseSaveGame)
	{
		return nullptr;
	}

	USROSaveGame* NewSaveGame = Cast<USROSaveGame>(BaseSaveGame);
	if (!NewSaveGame)
	{
		return nullptr;
	}

	NewSaveGame->AllChatPanelData.Add({
		.Position = {32, 800},
		.Size = {900, 250},
		.Tabs = {
			{
				.Name = "Default",
				.ChannelIds = {1},
				.CurrentChannel = 1,
				.bSelected = true
			}
		},
	});

	return NewSaveGame;
}
