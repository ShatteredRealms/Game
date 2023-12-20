// Copyright Shattered Realms Online All Rights Reserved

#pragma once
#include "ChatChannel.h"
#include "SSroChat/ChatMessage.h"

#include "SROChatMessage.generated.h"

/**
 * Chat message sent on a chat channel
 */
UCLASS(Blueprintable)
class UChatMessage : public UObject 
{
	GENERATED_BODY()

public:
	/** Channel the message was sent on */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGrpcSroChatChatChannel ChatChannelData;

	/** Chat message contents */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGrpcSroChatChatMessage ChatMessage;
};
