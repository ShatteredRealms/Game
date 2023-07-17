// Copyright Shattered Realms Online All Rights Reserved

#include "Chat/SROChatManager.h"

#include "TurboLinkGrpcConfig.h"
#include "TurboLinkGrpcManager.h"
#include "TurboLinkGrpcUtilities.h"
#include "Kismet/GameplayStatics.h"
#include "SRO/SRO.h"
#include "SRO/SROGameInstance.h"
#include "SSroChat/ChatService.h"

class UTurboLinkGrpcManager;

void USROChatManager::OnChatMessageReceived(const FGrpcContextHandle Handle, const FGrpcResult& Result, const FGrpcSroChatChatMessage& Message)
{
	UChatChannel* ChatChannel = GetChatChannelByHandle(Handle);
	if (!ChatChannel)
	{
		UE_LOG(LogSRO, Warning, TEXT("Unable to find chat channel for handle %d"), Handle.Value);
		return;
	}

	ChatChannel->Messages.Add(Message);
	ChatMessageReceivedDelegate.Broadcast(Message, ChatChannel->Struct.Id);
}

void USROChatManager::OnStatusChanged(FGrpcContextHandle Handle, EGrpcContextState NewState)
{
	UE_LOG(LogSRO, Display, TEXT("Status for %d changed to %d"), Handle.Value, NewState)
}

UChatChannel* USROChatManager::GetChatChannelByHandle(FGrpcContextHandle Handle)
{
	for (auto ChatChannel : ConnectedChannels)
	{
		if (ChatChannel->ContextHandle.Value == Handle.Value)
		{
			return ChatChannel;
		}
	}

	return nullptr;
}

void USROChatManager::InitService(USROGameInstance* OwningGameInstance)
{
	GameInstance = OwningGameInstance;
	
	TLM = UTurboLinkGrpcUtilities::GetTurboLinkGrpcManager(GetWorld());

	ChatService = Cast<UChatService>(TLM->MakeService("ChatService"));
	ChatServiceClient = ChatService->MakeClient();
	ChatServiceClient->OnConnectChannelResponse.AddUniqueDynamic(this, &USROChatManager::OnChatMessageReceived);
	ChatServiceClient->OnContextStateChange.AddUniqueDynamic(this, &USROChatManager::OnStatusChanged);
	ChatServiceClient->OnGetAuthorizedChatChannelsResponse.AddUniqueDynamic(this, &USROChatManager::OnGetAuthorizedChatChannelsResponse);

#if UE_BUILD_DEVELOPMENT
	ChatService->Connect(UTurboLinkGrpcUtilities::GetTurboLinkGrpcConfig()->GetServiceEndPoint(TEXT("ChatServiceDev")));
#else
	ChatService->Connect(UTurboLinkGrpcUtilities::GetTurboLinkGrpcConfig()->GetServiceEndPoint(TEXT("ChatServiceProd")));
#endif
}

void USROChatManager::ConnectAllChannels()
{
	// Request all authorized chat channels
	const FGrpcContextHandle Handle = ChatServiceClient->InitGetAuthorizedChatChannels();
	FGrpcSroCharacterCharacterTarget Request;
	Request.Type = FGrpcSroCharacterCharacterTargetType{};
	Request.Type.Id = GameInstance->SelectedCharacterId;
	ChatServiceClient->GetAuthorizedChatChannels(Handle, Request, GameInstance->AuthToken);
}

bool USROChatManager::ConnectToChannel(UChatChannel* ChatChannel, FString AuthToken)
{
	if (GetChannel(ChatChannel->Struct.Id)) return false;
	ConnectedChannels.Add(ChatChannel);

	// Connect
	// Make Request
	const FGrpcContextHandle Handle = ChatServiceClient->InitConnectChannel();
	FGrpcSroChatChatChannelTarget Request;
	Request.Id = ChatChannel->Struct.Id;
	ChatServiceClient->ConnectChannel(Handle, Request, AuthToken);

	// Relate data
	ChatChannel->ContextHandle = Handle;
	ChatChannel->Client = ChatServiceClient;

	// ChannelUpdated.ExecuteIfBound(ChatChannel);
	
	return true;
}

bool USROChatManager::ConnectDirectMessages()
{
	// TODO(wil): Implement
	if (GetDirectMessagesChannel()) return false;

	UChatChannel* ChatChannel = NewObject<UChatChannel>();
	ChatChannel->Struct.Id = 0;
	ChatChannel->Struct.Name = "Private Messages";

	UGameInstance* BGI = GetWorld()->GetGameInstance();
	if (!BGI) return false;
	USROGameInstance* GI = Cast<USROGameInstance>(BGI);
	if (!GI) return false;

	ConnectedChannels.Add(ChatChannel);

	// Connect to 
	
	return true;
}

UChatChannel* USROChatManager::GetDirectMessagesChannel()
{
	return GetChannel(FUInt64( 0 ));
}

UChatChannel* USROChatManager::GetChannel(int64 ChannelId)
{
	for (const auto ChatChannel : ConnectedChannels)
	{
		if (ChatChannel->Struct.Id.Value == ChannelId)
		{
			return ChatChannel;
		}
	}

	return nullptr;
}

TSet<UChatChannel*> USROChatManager::GetConnectedChannelsByIds(TSet<int64> ChannelIds)
{
	TSet<UChatChannel*> ChatChannels;
	for (const auto ChatChannel : ConnectedChannels)
	{
		if (ChannelIds.Contains(ChatChannel->Struct.Id.Value))
		{
			ChatChannels.Add(ChatChannel);
		}
	}

	return ChatChannels;
}

void USROChatManager::GetChatMessages(TSet<FUInt64> ChannelIds, TArray<FGrpcSroChatChatMessage>& Result)
{
	for (const int64 ChannelId : ChannelIds)
	{
		if (const UChatChannel* ChatChannel = GetChannel(ChannelId))
		{
			Result.Append(ChatChannel->Messages);
		}
	}
}

void USROChatManager::Disconnect()
{
	for (auto Channel : ConnectedChannels)
	{
		Channel->Client->TryCancel(Channel->ContextHandle);
	}

	ConnectedChannels.Empty();
}

USROChatManager::~USROChatManager()
{
	Disconnect();
}

void USROChatManager::OnGetAuthorizedChatChannelsResponse(
	FGrpcContextHandle Handle,
	const FGrpcResult& GrpcResult,
	const FGrpcSroChatChatChannels& Response)
{
	if (GrpcResult.Code != EGrpcResultCode::Ok)
	{
		UE_LOG(LogSRO, Error, TEXT("Error [%d]: %s"), GrpcResult.Code, *GrpcResult.Message)
		return;
	}
	
	Disconnect();
	
	for (auto ChatChannelData : Response.Channels)
	{
		UChatChannel* ChatChannel = NewObject<UChatChannel>();
		ChatChannel->Struct = ChatChannelData;
		ConnectToChannel(ChatChannel, GameInstance->AuthToken);
	}

	ConnectedAllChannelsDelegate.ExecuteIfBound();
}
