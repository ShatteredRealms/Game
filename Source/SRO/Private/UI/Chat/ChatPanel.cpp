// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Chat/ChatPanel.h"

#include "SRO/SRO.h"
#include "Util/SROChatWebLibrary.h"

UChatPanel::UChatPanel(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UChatTabWidget> FoundChatTabWidget(TEXT("/Game/SRO/UI/Chat/ChatTab"));
	ChatTabWidgetClass = FoundChatTabWidget.Class;
	
	static ConstructorHelpers::FClassFinder<UChatBoxWidget> FoundChatBoxWidget(TEXT("/Game/SRO/UI/Chat/ChatBox"));
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

	TSet<int64> ChannelIds;
	ChannelIds.Add(1);
	auto Tab = CreateTab(FText::FromString("All"), ChannelIds);	
	FocusTab(Tab);

	ChatTextBox->OnTextCommitted.AddDynamic(this, &UChatPanel::OnChatMessageSubmitted);
}


UChatTabWidget* UChatPanel::CreateTab(const FText& TabName, const TSet<int64> ChannelIds)
{
	// Create Tab
	UChatTabWidget* Tab = CreateWidget<UChatTabWidget>(PC, ChatTabWidgetClass);
	Tab->TabName->SetText(TabName);
	Tab->bSelected = true;
	Tab->OnChatTabSelected = &OnChatTabSelected;

	// Create chat box that holds tab messages
	UChatBoxWidget* ChatBox = CreateWidget<UChatBoxWidget>(PC, ChatBoxWidgetClass);
	ChatBox->SetupChat(ChannelIds);

	// Add to tab bar
	ChannelTabsHorizontalBox->AddChildToHorizontalBox(Tab);

	// Add to global chat tabs
	ChatTabs.Add(Tab, ChatBox);

	return Tab;
}

void UChatPanel::FocusTab(UChatTabWidget* Tab)
{
	for (const auto tab : ChatTabs)
	{
		if (tab.Key == Tab)
		{
			Tab->bSelected = true;
			MessagesScrollBox->ClearChildren();
			MessagesScrollBox->AddChild(tab.Value);
			CurrentTab = Tab;
		}
		else
		{
			tab.Key->bSelected = false;
		}
	}
}

UChatBoxWidget* UChatPanel::GetCurrentChatBox()
{
	return *ChatTabs.Find(CurrentTab);
}

void UChatPanel::OnChatMessageSubmitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod != ETextCommit::Type::OnEnter)
	{
		return;
	}
	
	GetCurrentChatBox()->SendChatMessage(Text);
	ChatTextBox->SetText({});
}
