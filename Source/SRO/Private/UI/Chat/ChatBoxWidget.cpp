// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Chat/ChatBoxWidget.h"

#include "HttpModule.h"
#include "SRO/SRO.h"
#include "SRO/SROPlayerController.h"
#include "Util/SROChatWebLibrary.h"
#include "Util/SROWebLibrary.h"

void UChatBoxWidget::OnChatMessageReceived(FChatMessageStruct ChatMessageStruct, int64 ChannelId)
{
	if (ConnectedToChannel(ChannelId))
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([this, ChatMessageStruct]()
		{
			UChatMessage* ChatMessage = NewObject<UChatMessage>();
			ChatMessage->ChatMessage = ChatMessageStruct;
			ChatMessageList->AddItem(ChatMessage);
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	}
}

void UChatBoxWidget::SetupChat(TSet<UChatChannel*> NewChatChannels, UChatChannel* NewCurrentChannel)
{
	if (bSetup) return;

	ChatChannels = NewChatChannels;
	CurrentChannel = NewCurrentChannel;

	ASROPlayerController* PC = Cast<ASROPlayerController>(GetOwningPlayer());
	if (!PC) return;

	PC->GetChatService()->ChatMessageReceivedDelegate.AddUObject(this, &UChatBoxWidget::OnChatMessageReceived);

	bSetup = true;
}

void UChatBoxWidget::SendChatMessage(const FText& Text)
{
	if (!CurrentChannel)
	{
		UE_LOG(LogSRO, Display, TEXT("No chat channel selected"));
		return;
	}
	
	ASROPlayerController* PC = Cast<ASROPlayerController>(GetOwningPlayer());
	if (!PC) return;

	const auto Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UChatBoxWidget::OnSendChatMessageResponse);

	
	USROChatWebLibrary::SendChatMessage(Text, CurrentChannel->Struct.Id, PC->AuthToken, Request);
}

void UChatBoxWidget::OnSendChatMessageResponse(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request,
                                               TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response,
                                               bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	const FString Message = USROWebLibrary::ValidateJsonResponse(bWasSuccessful, Response, JsonObject);
	if (Message != TEXT(""))
	{
		
	}
}

TSet<int64> UChatBoxWidget::GetChatChannelIds()
{
	TSet<int64> Ids;
	for (const auto Channel : ChatChannels)
	{
		Ids.Add(Channel->Struct.Id);
	}

	return Ids;
}

UChatChannel* UChatBoxWidget::ConnectedToChannel(int64 ChannelId)
{
	for (const auto Channel : ChatChannels)
	{
		if (Channel->Struct.Id == ChannelId)
		{
			return Channel;
		}
	}

	return nullptr;
}
