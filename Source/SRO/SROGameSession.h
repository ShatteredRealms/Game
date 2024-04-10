// Copyright 2022 Shattered Realms Online

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "SROGameSession.generated.h"

/**
 * 
 */
UCLASS(Config=Game)
class SRO_API ASROGameSession : public AGameSession
{
	GENERATED_BODY()

public:
	ASROGameSession();
	
	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "Auth")
	FString AuthClientId = "sro-gameserver";
	
	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "Auth")
	FString AuthClientSecret = "EgfOmuVQgHGSNpKzf6h0isJaDcRfKDWW";

	
};
