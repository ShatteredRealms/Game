// Copyright 2022 Shattered Realms Online


#include "Offline/SROOfflineGameMode.h"

#include "Offline/SROOfflineController.h"
#include "UI/Login/SROLoginHUD.h"

ASROOfflineGameMode::ASROOfflineGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SRO/Core/Login/Blueprints/BP_OfflinePawn"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	HUDClass = ASROLoginHUD::StaticClass();

	PlayerControllerClass = ASROOfflineController::StaticClass();
}
