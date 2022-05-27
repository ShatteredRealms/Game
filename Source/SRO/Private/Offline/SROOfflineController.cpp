// Copyright Shattered Realms Online All Rights Reserved


#include "Offline/SROOfflineController.h"

#include "UI/Login/SROLoginHUD.h"


// Called when the game starts
void ASROOfflineController::BeginPlay()
{
	Super::BeginPlay();

	if (const ASROLoginHUD* LoginHUD = StaticCast<ASROLoginHUD*>(GetHUD()))
	{
		FInputModeUIOnly Mode = FInputModeUIOnly();
		Mode.SetWidgetToFocus(LoginHUD->LoginWidget->TakeWidget());
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(Mode);
	}
}

