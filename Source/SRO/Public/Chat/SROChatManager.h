// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ChatChannel.h"
#include "TurboLinkGrpcClient.h"
#include "SSroChat/ChatMessage.h"
#include "SSroChat/ChatService.h"
#include "SROChatManager.generated.h"


DECLARE_MULTICAST_DELEGATE_TwoParams(FChatMessageReceivedDelegate, FGrpcSroChatChatMessage, int64)

// DECLARE_DELEGATE_OneParam(FChannelUpdatedDelegate, UChatChannel const* Channel);

DECLARE_DELEGATE(FConnectedAllChannelsDelegate);

class ASROPlayerController;
class USROGameInstance;

/**
 * Manages all chat connection functions for a player such as finding, connecting, and storing connections to
 * authorized chat channels. This manager needs to be initialized with a SROGameInstance before connecting to channels.
 */
UCLASS(Blueprintable)
class SRO_API USROChatManager : public UObject
{
	GENERATED_BODY()
	
 	/** Set of all connected chat channels */
 	UPROPERTY()
 	TSet<UChatChannel*> ConnectedChannels;

	/** Called when a message is received */
	UFUNCTION()
 	void OnChatMessageReceived(const FGrpcContextHandle Handle, const FGrpcResult& Result, const FGrpcSroChatChatMessage& Message);

	/** Called when a channel connection status is changed */
	UFUNCTION()
 	void OnStatusChanged(FGrpcContextHandle Handle, EGrpcContextState NewState);

	/** Called after connecting to all chat channels */
	FConnectedAllChannelsDelegate ConnectedAllChannelsDelegate;

	/**
	 * Gets a ChatChannel given a gRPC context
	 * @return UChatChannel pointer for the given gRPC context
	 */
	UChatChannel* GetChatChannelByHandle(FGrpcContextHandle Handle);
	
protected:
	/** TurboLinkGrpcManager used throughout this manager */
	UPROPERTY()
	UTurboLinkGrpcManager* TLM;

	/** SRO chat gRPC service */
	UPROPERTY()
	UChatService* ChatService;

	/** SRO chat gRPC client connection */
	UPROPERTY()
	UChatServiceClient* ChatServiceClient;

	/** GameInstance for this chat manager. */
	UPROPERTY()
	USROGameInstance* GameInstance;
	
 	/**
 	 * Attempts to connect to a chat channel for the given auth token.
 	 * @return true if the request to connect was made
 	 */
	UFUNCTION()
 	bool ConnectToChannel(UChatChannel* ChatChannel, FString AuthToken);
	
public:
	/** Initializes the chat manager. Necessary to be called during initialization once before anything else. */
	UFUNCTION()
	void InitService(USROGameInstance* OwningGameInstance);

	/** Attempts to connect to all chat channels */
	UFUNCTION()
	void ConnectAllChannels();

	/** Called after response for requesting authorized chat channels is received. */
	UFUNCTION()
	void OnGetAuthorizedChatChannelsResponse(FGrpcContextHandle Handle, const FGrpcResult& GrpcResult, const FGrpcSroChatChatChannels& Response);

	/** Delegate that broadcast when chat message is received on a connected chat channel */
 	FChatMessageReceivedDelegate ChatMessageReceivedDelegate;

 	/** Connect to the direct message stream and broadcast to the delegate */
 	UFUNCTION(BlueprintCallable, Category = "Chat")
 	bool ConnectDirectMessages();

 	/** If there is a current connection direct messages return it, otherwise return nullptr */
 	UFUNCTION(BlueprintCallable, Category = "Chat")
 	UChatChannel* GetDirectMessagesChannel();

 	/** If there is a current connection to the given ID return it, otherwise return nullptr */
 	UFUNCTION(BlueprintCallable, Category = "Chat")
 	UChatChannel* GetChannel(int64 ChannelId);

	/** Get all channels from the given channel ids */
 	UFUNCTION(BlueprintCallable, Category = "Chat")
 	TSet<UChatChannel*> GetConnectedChannelsByIds(TSet<int64> ChannelIds);

	/** Gets all the chat channels connections */
 	UFUNCTION(BlueprintCallable)
 	TSet<UChatChannel*> GetConnectedChannels() { return ConnectedChannels; }

	/** Adds all of the chat messages for the given chat channels into the result array. */
 	UFUNCTION(BlueprintCallable)
 	void GetChatMessages(TSet<FUInt64> ChannelIds, TArray<FGrpcSroChatChatMessage>& Result);

	/** Disconnects from all connected chat channels */
 	UFUNCTION(BlueprintCallable)
 	void Disconnect();

	/** On destroy disconnects from all channels gracefully */
 	virtual ~USROChatManager() override;

	/** Gets delegate for when all connection to all channels is made */
	FConnectedAllChannelsDelegate& OnConnectedAllChannels() { return ConnectedAllChannelsDelegate; }
};


