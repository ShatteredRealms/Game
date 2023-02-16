// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Chat/ChatChannel.h"
#include "Chat/ChatMessage.h"
#include "Components/ListView.h"
#include "Interfaces/IHttpRequest.h"
#include "ChatBoxWidget.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API UChatBoxWidget : public UUserWidget
{
	GENERATED_BODY()

	bool bSetup = false;

	/** The channel ids that will be shown in this chat */
	UPROPERTY(VisibleInstanceOnly, Category = "Chat")
	TSet<UChatChannel*> ChatChannels;

public:
	/** The current channel that is selected */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChatChannel* CurrentChannel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chat", meta = (BindWidget))
	UListView* ChatMessageList;

	UFUNCTION(BlueprintCallable)
	void SendChatMessage(const FText& Text);

	/** Required to initialize connection to chat servers. */
	UFUNCTION(BlueprintCallable)
	void SetupChat(TSet<UChatChannel*> NewChatChannels, UChatChannel* NewCurrentChannel);

	UFUNCTION(BlueprintCallable)
	TSet<UChatChannel*> GetChatChannel() { return ChatChannels; }

	UFUNCTION(BlueprintCallable)
	TSet<int64> GetChatChannelIds();

	UFUNCTION(BlueprintCallable)
	UChatChannel* ConnectedToChannel(int64 ChannelId);

private:
	// Internal event handlers
	
	/** Server response from chat message request */
	void OnSendChatMessageResponse(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request,
	                               TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful);

	/** Chat message received from the server on a subscribed channel */
	void OnChatMessageReceived(FChatMessageStruct ChatMessageStruct, int64 ChannelId);
};
