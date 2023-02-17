#pragma once

#include "ChatTabData.generated.h"

USTRUCT(BlueprintType)
struct FChatTabData
{
	GENERATED_BODY()

	/** The name of the chat tab */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	/** The chat channels that are in this tab */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<int64> ChannelIds;

	/** The current channel for the tab */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 CurrentChannel;

	/** Whether this tab was active or not */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSelected;
};
