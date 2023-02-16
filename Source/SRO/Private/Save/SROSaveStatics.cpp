// Copyright Shattered Realms Online All Rights Reserved


#include "Save/SROSaveStatics.h"

#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "SRO/SRO.h"
#include "SRO/SROGameInstance.h"
#include "UI/SROHud.h"


FString USROSaveStatics::GetSlotName(ASROPlayerController* PC)
{
	return Cast<USROGameInstance>(PC->GetGameInstance())->SelectedCharacterName;
}

bool USROSaveStatics::ResetSaveGame(ASROPlayerController* PC)
{
	if (!PC)
	{
		UE_LOG(LogSRO, Warning, TEXT("Invalid player controller received for save game"))
		return false;
	}

	UGameplayStatics::SaveGameToSlot(USROSaveGame::CreateDefault(), GetSlotName(PC), 0);

	return true;
}

USROSaveGame* USROSaveStatics::GetSaveGame(ASROPlayerController* PC)
{
	if (!PC)
	{
		UE_LOG(LogSRO, Warning, TEXT("Invalid player controller received for save game"))
		return nullptr;
	}
	
	if (UGameplayStatics::DoesSaveGameExist(GetSlotName(PC), 0))
	{
		USaveGame* BaseSaveGame = UGameplayStatics::LoadGameFromSlot(GetSlotName(PC), 0);
		if (BaseSaveGame)
		{
			return Cast<USROSaveGame>(BaseSaveGame);
		}

		UE_LOG(LogSRO, Error, TEXT("Failed loading saved game data"))
	}

	USROSaveGame* SaveGame = USROSaveGame::CreateDefault();

	if (!UGameplayStatics::SaveGameToSlot(SaveGame, GetSlotName(PC), 0))
	{
		UE_LOG(LogSRO, Error, TEXT("Failed saving name save"));
	}

	return SaveGame;
}

bool USROSaveStatics::SaveGame(ASROPlayerController* PC)
{
	USaveGame* BaseSaveGame = UGameplayStatics::CreateSaveGameObject(USROSaveGame::StaticClass());
	if (!BaseSaveGame)
	{
		UE_LOG(LogSRO, Warning, TEXT("Unable to create save game"))
		return false;
	}

	USROSaveGame* SaveGame = Cast<USROSaveGame>(BaseSaveGame);
	if (!SaveGame)
	{
		UE_LOG(LogSRO, Warning, TEXT("Unable to cast save game"))
		return false;
	}
	
	ASROHud* HUD = Cast<ASROHud>(PC->GetHUD());
	if (!HUD)
	{
		UE_LOG(LogSRO, Warning, TEXT("Unable to retrieve player HUD"))
		return false;
	}

	// Process chat channels
	for (const auto ChatChannel : HUD->BaseUI->ChatPanels)
	{
		FGeometry Geometry;
		UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(ChatChannel->Slot);
		if (!Slot)
		{
			UE_LOG(LogSRO, Error, TEXT("Invalid UI: Chat panel not in main canvas panel"))
			return false;
		}
		
		HUD->BaseUI->MainPanel->GetGeometryForSlot(Slot, Geometry);
		FChatPanelData ChatPanelData = {
			.Position = Geometry.Position,
			.Size = Geometry.Size,
		};

		for (const auto ChatTab : ChatChannel->ChatTabs)
		{
			ChatPanelData.Tabs.Add({
				.Name = ChatTab.Key->TabName->GetText().ToString(),
				.ChannelIds = ChatTab.Value->GetChatChannelIds(),
				.CurrentChannel = ChatTab.Value->CurrentChannel->Struct.Id,
				.bSelected = ChatTab.Key->IsSelected(),
			});
		}

		SaveGame->AllChatPanelData.Add(ChatPanelData);
	}

	UGameplayStatics::SaveGameToSlot(SaveGame, GetSlotName(PC), 0);

	return true;
}
