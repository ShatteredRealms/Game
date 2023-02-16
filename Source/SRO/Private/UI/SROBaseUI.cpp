// Copyright Shattered Realms Online All Rights Reserved


#include "UI/SROBaseUI.h"

#include "Components/CanvasPanelSlot.h"
#include "Save/SROSaveStatics.h"
#include "SRO/SRO.h"
#include "SRO/SROPlayerState.h"

USROBaseUI::USROBaseUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UChatPanel> FoundChatPanel(TEXT("/Game/SRO/Core/UI/Chat/ChatPanel"));
	ChatPanelClass = FoundChatPanel.Class;
}

bool USROBaseUI::SetupFromSave()
{
	for (auto ChatPanel : ChatPanels)
	{
		ChatPanel->RemoveFromParent();
	}
	
	ASROPlayerController* PC = Cast<ASROPlayerController>(GetOwningPlayer());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Invalid player controller type. Cannot setup UI."))
		return false;
	}

	USROSaveGame* SaveGame = USROSaveStatics::GetSaveGame(PC);

	if (!SaveGame)
	{
		UE_LOG(LogSRO, Warning, TEXT("Unable to load save game"))
		return false;
	}


	if (!ChatPanelClass)
	{
		UE_LOG(LogSRO, Warning, TEXT("Chat Panel Widget Class NOT found"));
		return false;
	}
	for (auto ChatPanelData : SaveGame->AllChatPanelData)
	{
		UChatPanel* ChatPanel = CreateWidget<UChatPanel>(GetWorld(), ChatPanelClass);
		if (!ChatPanel)
		{
			UE_LOG(LogSRO, Warning, TEXT("Chat Panel Widget NOT created"));
			return false;
		}
		
		ChatPanels.Add(ChatPanel);
		UCanvasPanelSlot* NewSlot = MainPanel->AddChildToCanvas(ChatPanel);
		NewSlot->SetPosition({ChatPanelData.Position.X, ChatPanelData.Position.Y});
		NewSlot->SetSize(ChatPanelData.Size);

		for (auto ChatTabData : ChatPanelData.Tabs)
		{
			const auto Channels = PC->GetChatService()->GetConnectedChannelsByIds(ChatTabData.ChannelIds);
			const auto CurrentChannel = PC->GetChatService()->ConnectedToChannel(ChatTabData.CurrentChannel);
			const auto Tab = ChatPanel->CreateTab(FText::FromString(ChatTabData.Name), Channels, CurrentChannel);

			if (!Tab)
			{
				UE_LOG(LogSRO, Warning, TEXT("Failed loading base UI: Could not create Chat Tab"))
			}
			else if (ChatTabData.bSelected)
			{
				ChatPanel->FocusTab(Tab);
			}
		}
	}

	return true;
}

void USROBaseUI::NativeConstruct()
{
	Super::NativeConstruct();
	SetupFromSave();
}
