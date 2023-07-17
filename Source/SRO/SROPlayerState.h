// Copyright 2022 Shattered Realms Online

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SROPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API ASROPlayerState : public APlayerState
{
	GENERATED_BODY()

	ASROPlayerState();
	
	virtual void BeginPlay() override;

	virtual FString GetPlayerNameCustom() const override;

public:
	UPROPERTY()
	FVector StartingLocation;
	
	UPROPERTY()
	FRotator StartingRotation;
};
