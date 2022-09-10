// Copyright Shattered Realms Online All Rights Reserved


#include "Offline/SROOfflineController.h"

#include "UI/Login/SROLoginHUD.h"


// Called when the game starts
void ASROOfflineController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly Mode = FInputModeUIOnly();
	
	if (const ASROLoginHUD* LoginHUD = StaticCast<ASROLoginHUD*>(GetHUD()))
	{
		// Mode.SetWidgetToFocus(LoginHUD->LoginWidget->TakeWidget());
	}
	
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(Mode);
}

void ASROOfflineController::Logout()
{
	AuthToken = nullptr;
	UserId = -1;
}

