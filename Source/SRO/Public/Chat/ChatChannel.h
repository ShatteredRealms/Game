#pragma once
#include "TurboLinkGrpcClient.h"
#include "SSroChat/ChatClient.h"
#include "SSroChat/ChatMessage.h"

#include "ChatChannel.generated.h"

/**
 * ChatChannel represents the details for a players connection to a Chat Channel. Storing the gRPC context, gRPC client,
 * chat channel details, and chat history.
 */
UCLASS(Blueprintable)
class UChatChannel : public UObject
{
	GENERATED_BODY()
	
public:
	/** gRPC context handle **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGrpcContextHandle ContextHandle;

	/** gRPC client connection to SRO chat service */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChatServiceClient* Client;

	/** Chat channel details */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGrpcSroChatChatChannel Struct;

	/** Cached received messages */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGrpcSroChatChatMessage> Messages;
};
