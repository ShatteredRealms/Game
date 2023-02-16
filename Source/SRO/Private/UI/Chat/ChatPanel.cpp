// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Chat/ChatPanel.h"

#include "SRO/SRO.h"
#include "UI/TabWidget.h"

UChatPanel::UChatPanel(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UTabWidget> FoundTabWidget(TEXT("/Game/SRO/Core/UI/BP_Tab"));
	TabWidgetClass = FoundTabWidget.Class;
	
	static ConstructorHelpers::FClassFinder<UChatBoxWidget> FoundChatBoxWidget(TEXT("/Game/SRO/Core/UI/Chat/ChatBox"));
	ChatBoxWidgetClass = FoundChatBoxWidget.Class;
}

void UChatPanel::NativeConstruct()
{
	Super::NativeConstruct();
	
	PC = Cast<ASROPlayerController>(GetOwningPlayer());
	if (!PC)
	{
		UE_LOG(LogSRO, Warning, TEXT("Unable to create chat panel due to invalid PlayerController"))
		return;
	}

	OnChatTabSelected.BindUObject(this, &UChatPanel::FocusTab);

	ChatTextBox->OnTextCommitted.AddDynamic(this, &UChatPanel::OnChatMessageSubmitted);
}


UTabWidget* UChatPanel::CreateTab(const FText& TabName, const TSet<UChatChannel*> ChatChannels, UChatChannel* CurrentChannel)
{
	// Create Tab
	UTabWidget* Tab = CreateWidget<UTabWidget>(PC, TabWidgetClass);

	if (!Tab)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to create tab"))
		return nullptr;
	}
	
	Tab->TabName->SetText(TabName);
	Tab->SetSelected(true);
	Tab->OnTabSelected = &OnChatTabSelected;

	// Create chat box that holds tab messages
	UChatBoxWidget* ChatBox = CreateWidget<UChatBoxWidget>(PC, ChatBoxWidgetClass);
	ChatBox->SetupChat(ChatChannels, CurrentChannel);

	// Add to tab bar
	ChannelTabsHorizontalBox->AddChildToHorizontalBox(Tab);

	// Add to global chat tabs
	ChatTabs.Add(Tab, ChatBox);

	return Tab;
}

void UChatPanel::FocusTab(UTabWidget* Tab)
{
	for (const auto tab : ChatTabs)
	{
		if (tab.Key == Tab)
		{
			Tab->SetSelected(true);
			MessagesScrollBox->ClearChildren();
			MessagesScrollBox->AddChild(tab.Value);
			CurrentTab = tab.Key;
			if (tab.Value->CurrentChannel)
			{
				ChatTextBox->SetHintText(FText::FromString(tab.Value->CurrentChannel->Struct.Name));
			}
			else
			{
				ChatTextBox->SetHintText(FText::FromString(""));
			}
		}
		else
		{
			tab.Key->SetSelected(false);
		}
	}
}

UChatBoxWidget* UChatPanel::GetCurrentChatBox()
{
	if (!CurrentTab)
	{
		return nullptr;
	}
	
	return *ChatTabs.Find(CurrentTab);
}

void UChatPanel::OnChatMessageSubmitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod != ETextCommit::Type::OnEnter)
	{
		return;
	}

	if (UChatBoxWidget* CurrentChatBox = GetCurrentChatBox())
	{
		CurrentChatBox->SendChatMessage(Text);
		ChatTextBox->SetText({});
	}
}
