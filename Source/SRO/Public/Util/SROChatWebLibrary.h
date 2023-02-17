// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"

#include "SROChatWebLibrary.generated.h"

/**
 *
 */
UCLASS()
class USROChatWebLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** Sends a chat message using the Web API */
	static void SendChatMessage(const ::FString& CharacterName, const ::FText& Message, FPlatformTypes::int64 ChannelId, ::FString AuthToken, TSharedRef
	                            <IHttpRequest, ESPMode::ThreadSafe> Request);
};
