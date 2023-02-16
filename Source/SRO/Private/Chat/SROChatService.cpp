// Copyright Shattered Realms Online All Rights Reserved

#include "Chat/SROChatService.h"
#include "Chat/ConnectChatTask.h"
#include "SRO/SRO.h"
#include "SRO/SROGameInstance.h"

USROChatService::USROChatService()
{
	ChatMessageReceivedDelegate.AddUObject(this, &USROChatService::OnChatMessageReceived);
}

void USROChatService::OnChatMessageReceived(FChatMessageStruct Message, int64 ChannelId)
{
	UChatChannel* ChatChannel = ConnectedToChannel(ChannelId);
	if (!ChatChannel)
	{
		UE_LOG(LogSRO, Warning, TEXT("Unable to find chat channel %d"), ChannelId);
		return;
	}

	ChatChannel->Messages.Add(Message);
}

bool USROChatService::ConnectToChannel(UChatChannel* ChatChannel, FString AuthToken)
{
	if (ConnectedToChannel(ChatChannel->Struct.Id)) return false;

	(new FAutoDeleteAsyncTask<FConnectChatTask>(ChatChannel->Struct.Id, "", AuthToken, &ChatMessageReceivedDelegate))->
		StartBackgroundTask();
	
	ConnectedChannels.Add(ChatChannel);
	return true;
}

bool USROChatService::ConnectDirectMessages(FString AuthToken)
{
	if (ConnectedToDirectMessages()) return false;

	UChatChannel* ChatChannel = NewObject<UChatChannel>();
	ChatChannel->Struct.Id = 0;
	ChatChannel->Struct.Name = "Private Messages";


	UGameInstance* BGI = GetWorld()->GetGameInstance();
	if (!BGI) return false;
	USROGameInstance* GI = Cast<USROGameInstance>(BGI);
	if (!GI) return false;
	
	(new FAutoDeleteAsyncTask<FConnectChatTask>(0, GI->SelectedCharacterName, AuthToken, &ChatMessageReceivedDelegate))->StartBackgroundTask();
	ConnectedChannels.Add(ChatChannel);
	return true;
}

UChatChannel* USROChatService::ConnectedToDirectMessages()
{
	return ConnectedToChannel(0);
}

UChatChannel* USROChatService::ConnectedToChannel(int64 ChannelId)
{
	for (const auto ChatChannel : ConnectedChannels)
	{
		if (ChatChannel->Struct.Id == ChannelId)
		{
			return ChatChannel;
		}
	}

	return nullptr;
}

TSet<UChatChannel*> USROChatService::GetConnectedChannelsByIds(TSet<int64> ChannelIds)
{
	TSet<UChatChannel*> ChatChannels;
	for (const auto ChatChannel : ConnectedChannels)
	{
		if (ChannelIds.Contains(ChatChannel->Struct.Id))
		{
			ChatChannels.Add(ChatChannel);
		}
	}

	return ChatChannels;
}

void USROChatService::GetChatMessages(TSet<int64> ChannelIds, TArray<FChatMessageStruct>& Result)
{
	for (const int64 ChannelId : ChannelIds)
	{
		if (const UChatChannel* ChatChannel = ConnectedToChannel(ChannelId))
		{
			Result.Append(ChatChannel->Messages);
		}
	}
}
