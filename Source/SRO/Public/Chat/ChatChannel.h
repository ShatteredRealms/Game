#pragma once
#include "ChatMessage.h"

#include "ChatChannel.generated.h"

USTRUCT(BlueprintType)
struct FChatChannelStruct
{
	GENERATED_BODY()
	
	/** The name of the chat tab */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 Id;

	/** The name of the chat tab */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
};

UCLASS(Blueprintable)
class UChatChannel : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FChatChannelStruct Struct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FChatMessageStruct> Messages;
};
