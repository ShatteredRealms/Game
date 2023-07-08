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

	SaveGame->AllChatPanelData.Empty();
	
	// Process chat channels
	for (const auto ChatChannel : HUD->BaseUI->ChatPanels)
	{
		FGeometry Geometry;
		UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(ChatChannel->Slot);
		if(!HUD->BaseUI->MainPanel->GetGeometryForSlot(Slot, Geometry))
		{
			UE_LOG(LogSRO, Error, TEXT("UI ERROR: Failed to get geometry for chat panel"));
			return false;
		}
		FChatPanelData ChatPanelData;
		ChatPanelData.Position = Geometry.Position;
		ChatPanelData.Size = Geometry.Size;

		for (const auto ChatTab : ChatChannel->TabMapping)
		{
			auto Value = Cast<UChatTabWidget>(ChatTab.Value);
			if (!Value)
			{
				UE_LOG(LogSRO, Error, TEXT("UI ERROR: Cannot load chat panel tab data"));
				return false;
			}
			
			FChatTabData Data;
			Data.Name = ChatTab.Key->TabName->GetText().ToString();
			Data.ChannelIds = Value->GetChatChannelIds();
			if (Value->ActiveChatChannel)
			{
				Data.CurrentChannel = Value->ActiveChatChannel->Struct.Id.Value;
			}
			Data.bSelected = ChatTab.Key->IsSelected();
			
			ChatPanelData.Tabs.Add(Data);
		}

		SaveGame->AllChatPanelData.Add(ChatPanelData);
	}

	return UGameplayStatics::SaveGameToSlot(SaveGame, GetSlotName(PC), 0);
}
