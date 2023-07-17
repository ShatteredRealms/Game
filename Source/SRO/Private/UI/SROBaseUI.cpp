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
	
	static ConstructorHelpers::FClassFinder<UAttackTargetsWidget> FoundAttackTargetsWidget(TEXT("/Game/SRO/Core/UI/Targeting/BP_AttackTargets"));
	if (FoundAttackTargetsWidget.Class != NULL)
	{
		AttackTargetsWidgetClass = FoundAttackTargetsWidget.Class;
	}
}

bool USROBaseUI::SetupFromSave()
{
	// Required to setup from save
	if (!PlayerController)
	{
		UE_LOG(LogSRO, Error, TEXT("Invalid player controller type. Cannot setup UI."))
		return false;
	}

	// Required to setup from save
	if (!ChatWindowClass)
	{
		UE_LOG(LogSRO, Error, TEXT("Chat Panel Widget Class NOT found"));
		return false;
	}

	// Load the save data
	USROSaveGame* SaveGame = USROSaveStatics::GetSaveGame(PlayerController);
	if (!SaveGame)
	{
		UE_LOG(LogSRO, Warning, TEXT("Unable to load save game or create default."))
		return false;
	}

	SetupChat(SaveGame->AllChatPanelData);

	return true;
}

void USROBaseUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	PlayerController = Cast<ASROPlayerController>(GetOwningPlayer());
	if (!PlayerController)
	{
		UE_LOG(LogSRO, Error, TEXT("Invalid player controller type."))
		return;
	}
	
	GameInstance = Cast<USROGameInstance>(GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(LogSRO, Error, TEXT("Invalid game instance"))
		return;
	}

	SetupFromSave();
}

void USROBaseUI::SetupChat(TArray<FChatPanelData> Data)
{
	// Delete old panels
	for (auto ChatPanel : ChatPanels)
	{
		ChatPanel->RemoveFromParent();
	}
	ChatPanels.Empty();

	// Load all chat panel data
	for (auto ChatPanelData : Data)
	{
		// Create the panel
		auto ChatPanel = CreateWidget<UDraggableResizableBaseWindow>(GetOwningPlayer(), ChatWindowClass);
		if (!ChatPanel)
		{
			UE_LOG(LogSRO, Warning, TEXT("Chat Panel Widget NOT created"));
			return;
		}
		// Track the panel
		ChatPanels.Add(ChatPanel);

		// Chat panels can't be closed
		ChatPanel->CloseButton->SetVisibility(ESlateVisibility::Hidden);

		// Place the panel
		UCanvasPanelSlot* NewSlot = MainPanel->AddChildToCanvas(ChatPanel);
		NewSlot->SetPosition({ChatPanelData.Position.X, ChatPanelData.Position.Y});
		NewSlot->SetSize(ChatPanelData.Size);

		// Create panel tabs
		for (auto ChatTabData : ChatPanelData.Tabs)
		{
			// Create the inner tab data
			auto ChatTab = CreateWidget<UChatTabWidget>(GetOwningPlayer(), ChatTabWidgetClass);
			if (!ChatTab)
			{
				UE_LOG(LogSRO, Warning, TEXT("Failed loading base UI: Could not create Chat Tab"))
				return;
			}
			ChatTab->SetupChat(
				GameInstance->ChatManager->GetConnectedChannelsByIds(ChatTabData.ChannelIds),
				GameInstance->ChatManager->GetChannel(ChatTabData.CurrentChannel));

			ChatTab->OnTabSelected.BindDynamic(this, &USROBaseUI::OnChatTabSelected);

			// Add tab to chat panel
			UTabWidget* Tab = ChatPanel->CreateTab(FText::FromString(ChatTabData.Name), ChatTab);
			if (!Tab)
			{
				UE_LOG(LogSRO, Warning, TEXT("Failed loading base UI: Could not create Chat Tab"))
				return;
			}

			// Select the tab is was previously selected
			if (ChatTabData.bSelected)
			{
				ChatPanel->FocusTab(Tab);
			}
		}
	}
}

void USROBaseUI::OnChatTabSelected(UChatTabWidget* SelectedChatTab)
{
	PrevFocusedChatTab = SelectedChatTab;
}

