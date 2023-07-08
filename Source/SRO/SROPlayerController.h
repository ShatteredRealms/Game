// Copyright 2022 Shattered Realms Online

#pragma once

#include "CoreMinimal.h"
#include "Chat/SROChatManager.h"
#include "Offline/SROOfflineController.h"
#include "SROPlayerController.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class SRO_API ASROPlayerController : public ASROOfflineController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void PreDisconnect();
};


