// Copyright Shattered Realms Online All Rights Reserved


#include "Offline/SROOfflineController.h"

#include "Auth/Keycloak/Keycloak.h"
#include "Net/UnrealNetwork.h"
#include "SRO/SRO.h"
#include "UI/Login/SROLoginHUD.h"

// Called when the game starts
void ASROOfflineController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly Mode = FInputModeUIOnly();
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(Mode);
}

