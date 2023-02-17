// Copyright 2022 Shattered Realms Online

#pragma once

#include "CoreMinimal.h"
#include "Character/SROBaseCharacter.h"
#include "Engine/GameInstance.h"
#include "SROGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API USROGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:	
	FString SelectedCharacterName;

	virtual void Shutdown() override;
};
