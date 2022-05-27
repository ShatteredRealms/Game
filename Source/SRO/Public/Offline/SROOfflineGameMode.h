// Copyright 2022 Shattered Realms Online

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SROOfflineGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API ASROOfflineGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	/** Initializes the Game Mode components */
	ASROOfflineGameMode();
};
