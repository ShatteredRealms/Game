// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/security/credentials.h>

#include "CoreMinimal.h"
#include "chat.grpc.pb.h"
#include "ChatMessage.h"
#include "../../../../Intermediate/ProjectFiles/ThirdParty/grpc/include/grpcpp/create_channel.h"
#include "UObject/NoExportTypes.h"
#include "SROChatService.generated.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using sro::chat::ChatService;
using sro::chat::ChannelIdMessage;
using sro::chat::ChatMessage;

DECLARE_MULTICAST_DELEGATE_TwoParams(FChatMessageReceivedDelegate, FChatMessageStruct, int64)

/**
 * 
 */
UCLASS(Blueprintable)
class SRO_API USROChatService : public UObject
{
	GENERATED_BODY()

	USROChatService();
	
private:
	/** Set of connected chat channel ids */
	TSet<int64> ConnectedChannels;

	TMap<int64, TArray<FChatMessageStruct>> ChannelChatMessages;

	void OnChatMessageReceived(FChatMessageStruct Message, int64 ChannelId);
	
public:
	/** Delegate that broadcast when chat message is received on a connected chat channel */
	FChatMessageReceivedDelegate ChatMessageReceivedDelegate;

	/** Connect to the channel id's message stream and broadcast to the delegate */
	UFUNCTION(BlueprintCallable, Category = "Chat")
	bool ConnectToChannel(int64 ChannelId, FString AuthToken);

	/** Connect to the direct message stream and broadcast to the delegate */
	UFUNCTION(BlueprintCallable, Category = "Chat")
	bool ConnectDirectMessages(FString AuthToken);

	/** If there is a current connection direct messages */
	UFUNCTION(BlueprintCallable, Category = "Chat")
	bool ConnectedToDirectMessages() { return ConnectedChannels.Contains(0); }

	/** If there is a current connection to the given Channel Id */
	UFUNCTION(BlueprintCallable, Category = "Chat")
	bool ConnectedToChannel(int64 ChannelId) { return ConnectedChannels.Contains(ChannelId); }

	UFUNCTION(BlueprintCallable)
	TSet<int64> GetConnectedChannels() { return ConnectedChannels; }

	UFUNCTION(BlueprintCallable)
	void GetChatMessages(TSet<int64> ChannelIds, TArray<FChatMessageStruct>& Result);
};
