// Copyright Shattered Realms Online All Rights Reserved

#include "Chat/SROChatService.h"
#include "Chat/ChatChannelWorker.h"
#include "SRO/SRO.h"
#include "SRO/SROGameInstance.h"

void USROChatService::OnChatMessageReceived(FChatMessageStruct Message, int64 ChannelId)
{
	UChatChannel* ChatChannel = ConnectedToChannel(ChannelId);
	if (!ChatChannel)
	{
		UE_LOG(LogSRO, Warning, TEXT("Unable to find chat channel %d"), ChannelId);
		return;
	}

	ChatChannel->Messages.Add(Message);
	ChatMessageReceivedDelegate.Broadcast(Message, ChannelId);
}

bool USROChatService::ConnectToChannel(UChatChannel* ChatChannel, FString AuthToken)
{
	if (ConnectedToChannel(ChatChannel->Struct.Id)) return false;

	TSharedPtr<FChatChannelWorker, ESPMode::ThreadSafe> Worker = MakeShared<FChatChannelWorker>(
		ChatChannel->Struct.Id, "", AuthToken);
	Worker->OnChatMessageReceived().AddUObject(this, &USROChatService::OnChatMessageReceived);
	Workers.Add(Worker);
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

	TSharedPtr<FChatChannelWorker, ESPMode::ThreadSafe> Worker = MakeShared<FChatChannelWorker>(
		ChatChannel->Struct.Id, GI->SelectedCharacterName, AuthToken);
	Worker->OnChatMessageReceived().AddUObject(this, &USROChatService::OnChatMessageReceived);
	Workers.Add(Worker);
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

void USROChatService::Shutdown()
{
	ConnectedChannels.Empty();
	
	for (const auto Worker : Workers)
	{
		Worker->Stop();
	}
	Workers.Empty();
}
