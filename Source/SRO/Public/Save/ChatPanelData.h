#pragma once

#include "ChatTabData.h"
#include "ChatPanelData.generated.h"


USTRUCT(BlueprintType)
struct FChatPanelData
{
	GENERATED_BODY()

	/** The location of the chat panel */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2f Position;

	/** The size of the chat panel */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Size;

	/** The tabs for this chat panel */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FChatTabData> Tabs;
};
