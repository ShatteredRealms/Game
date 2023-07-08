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
 * 
 */
UCLASS(Blueprintable)
class SRO_API USROChatManager : public UObject
{
	GENERATED_BODY()
	
 	/** Set of connected chat channel ids */
 	UPROPERTY()
 	TSet<UChatChannel*> ConnectedChannels;

	UFUNCTION()
 	void OnChatMessageReceived(const FGrpcContextHandle Handle, const FGrpcResult& Result, const FGrpcSroChatChatMessage& Message);

	UFUNCTION()
 	void OnStatusChanged(FGrpcContextHandle Handle, EGrpcContextState NewState);

	// FChannelUpdatedDelegate ChannelUpdated;

	FConnectedAllChannelsDelegate ConnectedAllChannelsDelegate;

	UChatChannel* GetChatChannelByHandle(FGrpcContextHandle Handle);
	
protected:
	UPROPERTY()
	UTurboLinkGrpcManager* TLM;
	
	UPROPERTY()
	UChatService* ChatService;

	UPROPERTY()
	APlayerController* Owner;

	UPROPERTY()
	UChatServiceClient* ChatServiceClient;

	UPROPERTY()
	USROGameInstance* GameInstance;
	
 	/** Connect to the channel id's message stream and broadcast to the delegate */
	UFUNCTION()
 	bool ConnectToChannel(UChatChannel* ChatChannel, FString AuthToken);
	
public:
	UFUNCTION()
	void InitService(USROGameInstance* OwningGameInstance);

	UFUNCTION()
	void ConnectAllChannels();

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
 	
 	UFUNCTION(BlueprintCallable, Category = "Chat")
 	TSet<UChatChannel*> GetConnectedChannelsByIds(TSet<int64> ChannelIds);

 	UFUNCTION(BlueprintCallable)
 	TSet<UChatChannel*> GetConnectedChannels() { return ConnectedChannels; }

 	UFUNCTION(BlueprintCallable)
 	void GetChatMessages(TSet<FUInt64> ChannelIds, TArray<FGrpcSroChatChatMessage>& Result);

 	UFUNCTION(BlueprintCallable)
 	void Disconnect();

 	virtual ~USROChatManager() override;

	// FChannelUpdatedDelegate& OnChannelUpdated() { return ChannelUpdated; }

	FConnectedAllChannelsDelegate& OnConnectedAllChannels() { return ConnectedAllChannelsDelegate; }
};


