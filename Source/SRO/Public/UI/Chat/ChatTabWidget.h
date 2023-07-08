// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Chat/ChatChannel.h"
#include "Chat/SROChatMessage.h"
#include "Components/EditableTextBox.h"
#include "Components/ListView.h"
#include "Interfaces/IHttpRequest.h"
#include "ChatTabWidget.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API UChatTabWidget : public UUserWidget
{
	GENERATED_BODY()

	bool bSetup = false;

	/** The channel ids that will be shown in this chat */
	UPROPERTY(VisibleInstanceOnly, Category = "Chat")
	TSet<UChatChannel*> ChatChannels;

	virtual void NativeConstruct() override;

public:
	/** The current channel that is selected */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChatChannel* ActiveChatChannel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chat", meta = (BindWidget))
	UListView* ChatMessageList;
	
	/** User chat input */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* ChatTextBox;

	UFUNCTION(BlueprintCallable)
	void SendChatMessage(const FText& Text);

	/** Required to initialize connection to chat servers. */
	UFUNCTION(BlueprintCallable)
	void SetupChat(TSet<UChatChannel*> NewChatChannels, UChatChannel* NewCurrentChannel);

	UFUNCTION(BlueprintCallable)
	TSet<UChatChannel*> GetChatChannels() { return ChatChannels; }

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
	void OnChatMessageReceived(FGrpcSroChatChatMessage ChatMessageStruct, int64 ChannelId);

private:
	// Call when a chat message should be submitted
	UFUNCTION()
	void OnChatMessageSubmitted(const FText& Text, ETextCommit::Type CommitMethod);
};

