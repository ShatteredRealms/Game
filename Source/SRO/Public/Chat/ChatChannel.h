#pragma once
#include "TurboLinkGrpcClient.h"
#include "SSroChat/ChatClient.h"
#include "SSroChat/ChatMessage.h"

#include "ChatChannel.generated.h"

UCLASS(Blueprintable)
class UChatChannel : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGrpcContextHandle ContextHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChatServiceClient* Client;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGrpcSroChatChatChannel Struct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGrpcSroChatChatMessage> Messages;
};
