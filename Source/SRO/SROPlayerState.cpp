// Copyright 2022 Shattered Realms Online


#include "SROPlayerState.h"

ASROPlayerState::ASROPlayerState() : Super()
{
	bUseCustomPlayerNames = 0;
}

void ASROPlayerState::BeginPlay()
{
	Super::BeginPlay();

	bUseCustomPlayerNames = 0;
}

FString ASROPlayerState::GetPlayerNameCustom() const
{
	return Super::GetPlayerNameCustom();
}
