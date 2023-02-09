// Copyright Shattered Realms Online All Rights Reserved

#include "Chat/SROChatService.h"
#include "Chat/ConnectChatTask.h"

USROChatService::USROChatService()
{
	ChatMessageReceivedDelegate.AddUObject(this, &USROChatService::OnChatMessageReceived);
}

void USROChatService::OnChatMessageReceived(FChatMessageStruct Message, int64 ChannelId)
{
	if (!ChannelChatMessages.Contains(ChannelId))
	{
		ChannelChatMessages.Add(ChannelId);
	}
	
	TArray<FChatMessageStruct>* ChatMessages = ChannelChatMessages.Find(ChannelId);
	ChatMessages->Add(Message);
}

bool USROChatService::ConnectToChannel(int64 ChannelId, FString AuthToken)
{
	if (ConnectedChannels.Contains(ChannelId)) return false;

	(new FAutoDeleteAsyncTask<FConnectChatTask>(ChannelId, AuthToken, &ChatMessageReceivedDelegate))->
		StartBackgroundTask();
	
	ConnectedChannels.Add(ChannelId);
	return true;
}

bool USROChatService::ConnectDirectMessages(FString AuthToken)
{
	if (ConnectedChannels.Contains(0)) return false;

	(new FAutoDeleteAsyncTask<FConnectChatTask>(0, AuthToken, &ChatMessageReceivedDelegate))->StartBackgroundTask();
	ConnectedChannels.Add(0);
	return true;
}

void USROChatService::GetChatMessages(TSet<int64> ChannelIds, TArray<FChatMessageStruct>& Result)
{
	for (const int64 ChannelId : ChannelIds)
	{
		Result.Append(*ChannelChatMessages.Find(ChannelId));
	}
}
