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

	NewSaveGame->CreateDefault_Chat();
	NewSaveGame->CreateDefault_CombatBarPositions();
	NewSaveGame->CreateDefault_TargetingPosition();

	return NewSaveGame;
}

void USROSaveGame::CreateDefault_CombatBarPositions()
{
	HealthBarPosition = FVector2d{12.0f, 12.0f};
	ManaBarPosition = FVector2D{32.0f, 12.0f};
	ExperienceBarPosition = FVector2D{52.0f, 12.0f};
}

void USROSaveGame::CreateDefault_Chat()
{
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
	
	AllChatPanelData.Add(ChatPanel);
}

void USROSaveGame::CreateDefault_TargetingPosition()
{
	// @TODO(wil): Calculate screen size and set in the middle
	AttackTargetsPosition = FVector2D{500, 12};
}
