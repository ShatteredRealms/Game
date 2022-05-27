// Copyright 2022 Shattered Realms Online


#include "Offline/SROOfflineGameMode.h"

#include "UI/Login/SROLoginHud.h"

ASROOfflineGameMode::ASROOfflineGameMode()
{
	HUDClass = ASROLoginHud::StaticClass();
}
