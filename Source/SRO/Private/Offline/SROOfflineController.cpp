// Copyright Shattered Realms Online All Rights Reserved


#include "Offline/SROOfflineController.h"

#include "Net/UnrealNetwork.h"
#include "UI/Login/SROLoginHUD.h"


// Called when the game starts
void ASROOfflineController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly Mode = FInputModeUIOnly();
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(Mode);
}

void ASROOfflineController::Logout()
{
	AuthToken = nullptr;
	UserId = -1;
}

void ASROOfflineController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ASROOfflineController, AuthToken, COND_OwnerOnly);
}

