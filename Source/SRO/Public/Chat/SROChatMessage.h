// Copyright Shattered Realms Online All Rights Reserved

#pragma once
#include "ChatChannel.h"
#include "SSroChat/ChatMessage.h"

#include "SROChatMessage.generated.h"

UCLASS(Blueprintable)
class UChatMessage : public UObject 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGrpcSroChatChatChannel ChatChannelData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGrpcSroChatChatMessage ChatMessage;
};
