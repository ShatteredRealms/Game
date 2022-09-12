// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Login/SROCreateCharacterWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Offline/SROOfflineController.h"
#include "SRO/SRO.h"
#include "UI/Login/SROLoginHUD.h"
#include "Util/SROCharactersWebLibrary.h"
#include "Util/SROWebLibrary.h"

void USROCreateCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Http = &FHttpModule::Get();
}

void USROCreateCharacterWidget::Reset()
{
	// @TODO(wil): Reset all selections
	NameTextBox->SetText(FText());
}

void USROCreateCharacterWidget::CreateCharacter()
{
	// @TODO(wil): Validate character name before making request
	
	const auto Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &USROCreateCharacterWidget::OnCreateCharacterResponse);

	ASROOfflineController* PC = Cast<ASROOfflineController>(GetPlayerContext().GetPlayerController());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get player controller"))
		return;
	}

	// @TODO(wil): Read from the lists to get the gender and realm ids
	USROCharactersWebLibrary::CreateCharacter(Request, PC->AuthToken, PC->UserId, NameTextBox->GetText().ToString(), 1, 1);
}

void USROCreateCharacterWidget::Cancel()
{
	ASROOfflineController* PC = Cast<ASROOfflineController>(GetPlayerContext().GetPlayerController());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get player controller"))
		return;
	}

	const ASROLoginHUD* HUD = Cast<ASROLoginHUD>(PC->GetHUD());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get HUD"))
		return;
	}

	HUD->LoginCompleted();
}

void USROCreateCharacterWidget::Logout()
{
	ASROOfflineController* PC = Cast<ASROOfflineController>(GetPlayerContext().GetPlayerController());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get player controller"))
		return;
	}

	PC->Logout();
	
	ASROLoginHUD* HUD = Cast<ASROLoginHUD>(PC->GetHUD());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get HUD"))
		return;
	}

	HUD->LogoutCompleted();
}

void USROCreateCharacterWidget::OnCreateCharacterResponse(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	const FString Message = USROWebLibrary::ValidateJsonResponse(bWasSuccessful, Response, JsonObject); 
	if (Message != TEXT(""))
	{
		ErrorText->SetText(FText::FromString(Message));
		ErrorText->SetVisibility(ESlateVisibility::Visible);
		return;
	}

	
	ASROOfflineController* PC = Cast<ASROOfflineController>(GetPlayerContext().GetPlayerController());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get player controller"))
		return;
	}

	ASROLoginHUD* HUD = Cast<ASROLoginHUD>(PC->GetHUD());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get HUD"))
		return;
	}

	HUD->LoginCompleted();
}
