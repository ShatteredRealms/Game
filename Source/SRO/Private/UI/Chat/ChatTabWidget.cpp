// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Chat/ChatTabWidget.h"

#include "HttpModule.h"
#include "SRO/SRO.h"
#include "SRO/SROGameInstance.h"
#include "SRO/SROPlayerController.h"
#include "Util/SROChatWebLibrary.h"
#include "Util/SROWebLibrary.h"
#include "TurboLinkGrpcMessage.h"


void UChatTabWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ChatTextBox->OnTextCommitted.AddDynamic(this, &UChatTabWidget::OnChatMessageSubmitted);
}

void UChatTabWidget::OnChatMessageReceived(FGrpcSroChatChatMessage ChatMessageStruct, int64 ChannelId)
{
	if (ConnectedToChannel(ChannelId))
	{
		UChatMessage* ChatMessage = NewObject<UChatMessage>();
		ChatMessage->ChatMessage = ChatMessageStruct;
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
	ChatTextBox->SetText({});
}

void UChatTabWidget::SetupChat(TSet<UChatChannel*> NewChatChannels, UChatChannel* NewCurrentChannel)
{
	if (bSetup) return;

	ChatChannels = NewChatChannels;
	ActiveChatChannel = NewCurrentChannel;
	
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
