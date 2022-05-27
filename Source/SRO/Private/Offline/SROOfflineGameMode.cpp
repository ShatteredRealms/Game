// Copyright 2022 Shattered Realms Online


#include "Offline/SROOfflineGameMode.h"

#include "UI/Login/SROLoginHUD.h"

ASROOfflineGameMode::ASROOfflineGameMode()
{
	HUDClass = ASROLoginHUD::StaticClass();
}
