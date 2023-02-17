// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ChatPanelData.h"
#include "GameFramework/SaveGame.h"
#include "SRO/SROPlayerController.h"
#include "SROSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API USROSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FChatPanelData> AllChatPanelData;

	static USROSaveGame* CreateDefault();
};
