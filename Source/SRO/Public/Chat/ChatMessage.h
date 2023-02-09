// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "ChatMessage.generated.h"

USTRUCT(BlueprintType)
struct FChatMessageStruct
{
	GENERATED_BODY()

	/** Sender's username */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Username = "";

	/** Message body of the chat message */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Message = "";
};

UCLASS(Blueprintable)
class UChatMessage : public UObject 
{
	GENERATED_BODY()

	
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FChatMessageStruct ChatMessage;

	UFUNCTION(BlueprintCallable)
	FString GenerateText();
};
