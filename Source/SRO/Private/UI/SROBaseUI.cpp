// Copyright Shattered Realms Online All Rights Reserved


#include "UI/SROBaseUI.h"

#include "Components/CanvasPanelSlot.h"
#include "Save/SROSaveStatics.h"
#include "SRO/SRO.h"
#include "SRO/SROGameInstance.h"
#include "SRO/SROPlayerState.h"
#include "UI/Chat/ChatTabWidget.h"

USROBaseUI::USROBaseUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UDraggableResizableBaseWindow> FoundChatWindow(TEXT("/Game/SRO/Core/UI/BP_DragResizeBaseWindow"));
	if (FoundChatWindow.Class != NULL)
	{
		ChatWindowClass = FoundChatWindow.Class;
	}
	
	
	static ConstructorHelpers::FClassFinder<UChatTabWidget> FoundChatTabWidget(TEXT("/Game/SRO/Core/UI/Chat/BP_ChatTabWidget"));
	if (FoundChatTabWidget.Class != NULL)
	{
		ChatTabWidgetClass = FoundChatTabWidget.Class;
	}
}

bool USROBaseUI::SetupFromSave()
{
	for (auto ChatPanel : ChatPanels)
	{
		ChatPanel->RemoveFromParent();
	}
	ChatPanels.Empty();
	
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

	if (!ChatWindowClass)
	{
		UE_LOG(LogSRO, Error, TEXT("Chat Panel Widget Class NOT found"));
		return false;
	}

	USROGameInstance* GI = Cast<USROGameInstance>(GetGameInstance());
	if (!GI)
	{
		UE_LOG(LogSRO, Error, TEXT("Invalid game instance"))
		return false;
	}
	
	for (auto ChatPanelData : SaveGame->AllChatPanelData)
	{
		auto ChatPanel = CreateWidget<UDraggableResizableBaseWindow>(GetOwningPlayer(), ChatWindowClass);
		if (!ChatPanel)
		{
			UE_LOG(LogSRO, Warning, TEXT("Chat Panel Widget NOT created"));
			return false;
		}
		ChatPanel->CloseButton->SetVisibility(ESlateVisibility::Hidden);
		
		ChatPanels.Add(ChatPanel);
		UCanvasPanelSlot* NewSlot = MainPanel->AddChildToCanvas(ChatPanel);
		NewSlot->SetPosition({ChatPanelData.Position.X, ChatPanelData.Position.Y});
		NewSlot->SetSize(ChatPanelData.Size);

		for (auto ChatTabData : ChatPanelData.Tabs)
		{
			TSet<UChatChannel*> Channels = GI->ChatManager->GetConnectedChannelsByIds(ChatTabData.ChannelIds);
			UChatChannel* CurrentChannel = GI->ChatManager->GetChannel(ChatTabData.CurrentChannel);

			auto ChatTab = CreateWidget<UChatTabWidget>(GetOwningPlayer(), ChatTabWidgetClass);
			if (!ChatTab)
			{
				UE_LOG(LogSRO, Warning, TEXT("Failed loading base UI: Could not create Chat Tab"))
			}
			
			ChatTab->SetupChat(Channels, CurrentChannel);
			
			UTabWidget* Tab = ChatPanel->CreateTab(FText::FromString(ChatTabData.Name), ChatTab);

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
