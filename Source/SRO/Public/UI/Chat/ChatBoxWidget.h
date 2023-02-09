// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	TSet<int64> ChannelIds;

public:
	/** The current channel that is selected */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 CurrentChannel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chat", meta = (BindWidget))
	UListView* ChatMessageList;

	UFUNCTION(BlueprintCallable)
	void SendChatMessage(const FText& Text);

	/** Required to be to initialize connection to chat servers. */
	UFUNCTION()
	void SetupChat(TSet<int64> SubscribedChannelIds);

	UFUNCTION(BlueprintCallable)
	TSet<int64> GetChannelIds() { return ChannelIds; }


private:
	// Internal event handlers
	
	/** Server response from chat message request */
	void OnSendChatMessageResponse(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request,
	                               TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful);

	/** Chat message received from the server on a subscribed channel */
	void OnChatMessageReceived(FChatMessageStruct ChatMessage, int64 ChannelId);
};
