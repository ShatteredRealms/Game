// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Chat/ChatBoxWidget.h"

#include "HttpModule.h"
#include "SRO/SROPlayerController.h"
#include "Util/SROChatWebLibrary.h"
#include "Util/SROWebLibrary.h"

void UChatBoxWidget::OnChatMessageReceived(FChatMessageStruct ChatMessageStruct, int64 ChannelId)
{
	if (ChannelIds.Contains(ChannelId))
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([this, ChatMessageStruct]()
		{
			UChatMessage* ChatMessage = NewObject<UChatMessage>();
			ChatMessage->ChatMessage = ChatMessageStruct;
			ChatMessageList->AddItem(ChatMessage);
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	}
}

void UChatBoxWidget::SetupChat(TSet<int64> SubscribedChannelIds)
{
	if (bSetup) return;

	ChannelIds = SubscribedChannelIds;
	for (auto Id : SubscribedChannelIds)
	{
		CurrentChannel = Id;
		break;
	}

	ASROPlayerController* PC = Cast<ASROPlayerController>(GetOwningPlayer());
	if (!PC) return;

	PC->ChatService->ChatMessageReceivedDelegate.AddUObject(this, &UChatBoxWidget::OnChatMessageReceived);

	bSetup = true;
}

void UChatBoxWidget::SendChatMessage(const FText& Text)
{
	ASROPlayerController* PC = Cast<ASROPlayerController>(GetOwningPlayer());
	if (!PC) return;

	const auto Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UChatBoxWidget::OnSendChatMessageResponse);

	USROChatWebLibrary::SendChatMessage(Text, CurrentChannel, PC->AuthToken, Request);
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
