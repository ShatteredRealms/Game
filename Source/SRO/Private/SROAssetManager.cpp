// Copyright Shattered Realms Online All Rights Reserved


#include "SROAssetManager.h"

#include "AbilitySystemGlobals.h"

void USROAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
