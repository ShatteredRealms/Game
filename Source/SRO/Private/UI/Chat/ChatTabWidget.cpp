// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Chat/ChatTabWidget.h"

#include "HttpModule.h"
#include "SRO/SRO.h"
#include "SRO/SROGameInstance.h"
#include "SRO/SROPlayerController.h"
#include "Util/SROChatWebLibrary.h"
#include "Util/SROWebLibrary.h"
#include "TurboLinkGrpcMessage.h"
#include "Chat/SROChatMessage.h"


UChatTabWidget::UChatTabWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SetIsFocusable(true);
}

void UChatTabWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ChatTextBox->OnTextCommitted.AddDynamic(this, &UChatTabWidget::OnChatMessageSubmitted);
}

void UChatTabWidget::OnChatMessageReceived(FGrpcSroChatChatMessage ChatMessageStruct, int64 ChannelId)
{
	const auto ChatChannel = ConnectedToChannel(ChannelId);
	if (ChatChannel)
	{
		UChatMessage* ChatMessage = NewObject<UChatMessage>();
		ChatMessage->ChatMessage = ChatMessageStruct;
		ChatMessage->ChatChannelData = ChatChannel->Struct;
		ChatMessageList->AddItem(ChatMessage);
	}
}

void UChatTabWidget::OnChatMessageSubmitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod != ETextCommit::Type::OnEnter)
	{
		return;
	}

	// @TODO(wil): Handle commands

	SendChatMessage(Text);
	ChatTextBox->SetText(FText::FromString(""));
	ChatTextBox->SetError(FText::FromString("Example Error"));
	SetFocus();
}

void UChatTabWidget::SetupChat(TSet<UChatChannel*> NewChatChannels, UChatChannel* NewCurrentChannel)
{
	if (bSetup) return;

	ChatChannels = NewChatChannels;
	ChangeActiveChatChannel(NewCurrentChannel);
	
	USROGameInstance* GI = Cast<USROGameInstance>(GetGameInstance());
	if (!GI)
	{
		UE_LOG(LogSRO, Error, TEXT("Invalid game instance"))
		return;
	}

	GI->ChatManager->ChatMessageReceivedDelegate.AddUObject(this, &UChatTabWidget::OnChatMessageReceived);

	bSetup = true;
}

void UChatTabWidget::SendChatMessage(const FText& Text)
{
	if (!ActiveChatChannel)
	{
		UE_LOG(LogSRO, Display, TEXT("No chat channel selected"));
		return;
	}
	
	OnTabSelected.ExecuteIfBound(this);
	
	ASROPlayerController* PC = Cast<ASROPlayerController>(GetOwningPlayer());
	if (!PC) return;

	const auto Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UChatTabWidget::OnSendChatMessageResponse);

	USROGameInstance* GI = Cast<USROGameInstance>(GetGameInstance());
	if (!GI) return;
	
	USROChatWebLibrary::SendChatMessage(GI->SelectedCharacterName, Text, ActiveChatChannel->Struct.Id, GI->AuthToken, Request);
}

void UChatTabWidget::OnSendChatMessageResponse(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request,
                                               TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response,
                                               bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	const FString Message = USROWebLibrary::ValidateJsonResponse(bWasSuccessful, Response, JsonObject);
	if (Message != TEXT(""))
	{
		
	}
}

TSet<int64> UChatTabWidget::GetChatChannelIds()
{
	TSet<int64> Ids;
	for (const auto Channel : ChatChannels)
	{
		Ids.Add(Channel->Struct.Id.Value);
	}

	return Ids;
}

UChatChannel* UChatTabWidget::ConnectedToChannel(int64 ChannelId)
{
	for (const auto Channel : ChatChannels)
	{
		if (Channel->Struct.Id.Value == ChannelId)
		{
			return Channel;
		}
	}

	return nullptr;
}

UChatChannel* UChatTabWidget::ChangeActiveChatChannel(UChatChannel* ChatChannel)
{
	if (!ChatChannel)
	{
		return nullptr;
	}

	ActiveChatChannel = ChatChannel;
	ChatTextBox->SetHintText(FText::FromString(ChatChannel->Struct.Name));
	return ChatChannel;
}

FReply UChatTabWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Tab &&
		ChatChannels.Num() > 0 &&
		!ChatDropDown->IsVisible())
	{
		ChatDropDown->Entries->ClearListItems();
		for (const auto ChatChannel : ChatChannels)
		{
			UDropDownData* Data = NewObject<UDropDownData>();
			Data->Name = ChatChannel->Struct.Name;
			Data->DataObject = ChatChannel;
			Data->OnClicked.AddDynamic(this, &UChatTabWidget::OnDropDownClicked);
			ChatDropDown->AddEntry(Data);

			if (ActiveChatChannel == ChatChannel)
			{
				ChatDropDown->Entries->SetSelectedItem(Data);
			}
		}
		ChatDropDown->SetVisibility(ESlateVisibility::Visible);
		ChatDropDown->SetFocus();
		
		return FReply::Handled();
	}
	
	return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
}

FReply UChatTabWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	if (InFocusEvent.GetCause() == EFocusCause::SetDirectly)
	{
		ChatTextBox->SetFocus();
		OnTabSelected.ExecuteIfBound(this);
	}
	
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UChatTabWidget::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	OnTabSelected.ExecuteIfBound(this);
	Super::NativeOnAddedToFocusPath(InFocusEvent);
}

void UChatTabWidget::OnDropDownClicked(UDropDownData* ClickedData)
{
	auto ChatChannel = Cast<UChatChannel>(ClickedData->DataObject);
	if (!ChatChannel)
	{
		UE_LOG(LogSRO, Error, TEXT("Invalid drop down data object"))
		return;
	}

	ChangeActiveChatChannel(ChatChannel);
	ChatDropDown->Clear();
	ChatTextBox->SetFocus();
}
