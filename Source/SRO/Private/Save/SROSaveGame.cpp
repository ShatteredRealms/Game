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

	FChatPanelData ChatPanel;
	
	FVector2f Position;
	Position.X = 32;
	Position.Y = 800;
	ChatPanel.Position = Position;
	
	FVector2D Size;
	Size.X = 900;
	Size.Y = 250;
	ChatPanel.Size = Size;

	FChatTabData DefaultTab;
	DefaultTab.Name = "Default";
	DefaultTab.ChannelIds.Add(FUInt64(1));
	DefaultTab.CurrentChannel = FUInt64(1);
	DefaultTab.bSelected = true;

	ChatPanel.Tabs.Add(DefaultTab);

	NewSaveGame->AllChatPanelData.Add(ChatPanel);

	return NewSaveGame;
}
