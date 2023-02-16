// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/security/credentials.h>

#include "CoreMinimal.h"
#include "chat.grpc.pb.h"
#include "ChatChannel.h"
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
	UPROPERTY()
	TSet<UChatChannel*> ConnectedChannels;


	void OnChatMessageReceived(FChatMessageStruct Message, int64 ChannelId);
	
public:
	/** The character name used when sending messages */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString CharacterName;
	
	/** Delegate that broadcast when chat message is received on a connected chat channel */
	FChatMessageReceivedDelegate ChatMessageReceivedDelegate;

	/** Connect to the channel id's message stream and broadcast to the delegate */
	UFUNCTION(BlueprintCallable, Category = "Chat")
	bool ConnectToChannel(UChatChannel* ChatChannel, FString AuthToken);

	/** Connect to the direct message stream and broadcast to the delegate */
	UFUNCTION(BlueprintCallable, Category = "Chat")
	bool ConnectDirectMessages(FString AuthToken);

	/** If there is a current connection direct messages return it, otherwise return nullptr */
	UFUNCTION(BlueprintCallable, Category = "Chat")
	UChatChannel* ConnectedToDirectMessages();

	/** If there is a current connection to the given ID return it, otherwise return nullptr */
	UFUNCTION(BlueprintCallable, Category = "Chat")
	UChatChannel* ConnectedToChannel(int64 ChannelId);
	
	UFUNCTION(BlueprintCallable, Category = "Chat")
	TSet<UChatChannel*> GetConnectedChannelsByIds(TSet<int64> ChannelIds);

	UFUNCTION(BlueprintCallable)
	TSet<UChatChannel*> GetConnectedChannels() { return ConnectedChannels; }

	UFUNCTION(BlueprintCallable)
	void GetChatMessages(TSet<int64> ChannelIds, TArray<FChatMessageStruct>& Result);
};
