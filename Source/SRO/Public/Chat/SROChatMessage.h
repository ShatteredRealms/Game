// Copyright Shattered Realms Online All Rights Reserved

#pragma once
#include "SSroChat/ChatMessage.h"

#include "SROChatMessage.generated.h"

UCLASS(Blueprintable)
class UChatMessage : public UObject 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGrpcSroChatChatMessage ChatMessage;

	UFUNCTION(BlueprintCallable)
	FString GenerateText();
};
