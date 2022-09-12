// Copyright 2022 Shattered Realms Online


#include "UI/Login/SROLoginWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Offline/SROOfflineController.h"
#include "SRO/SRO.h"
#include "Util/SROAccountsWebLibrary.h"
#include "Util/SROWebLibrary.h"

USROLoginWidget::USROLoginWidget(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (LoginPanel)
	{	
		LoginPanel->SetVisibility(ESlateVisibility::Visible);
	}

	Http = &FHttpModule::Get();
}

void USROLoginWidget::OnLoginRequestReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	const FString Message = USROWebLibrary::ValidateJsonResponse(bWasSuccessful, Response, JsonObject); 
	if (Message != TEXT(""))
	{
		const FString ErrorMessage =
			Message == "Error 401" ?
				"Invalid email and password" : Message+" while logging in";

		LoginFailed(ErrorMessage);
		return;
	}

	OnSuccessfulLogin(JsonObject->GetStringField("token"), JsonObject->GetIntegerField("id"));
}

void USROLoginWidget::LoginFailed(const FString Message) const
{
	LoginErrorText->SetVisibility(ESlateVisibility::Visible);
	LoginErrorText->SetText(FText::FromString(Message));
	PasswordTextBox->SetText(FText::FromString(TEXT("")));
	LoginButton->SetIsEnabled(true);
}

void USROLoginWidget::Login()
{
	if (EmailTextBox->GetText().ToString() == "")
	{
		LoginFailed("Email cannot be empty");
		return;
	}
	
	if (PasswordTextBox->GetText().ToString() == "")
	{
		LoginFailed("Password cannot be empty");
		return;
	}
	
	LoginButton->SetIsEnabled(false);
	LoginErrorText->SetVisibility(ESlateVisibility::Hidden);

	const auto Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &USROLoginWidget::OnLoginRequestReceived);

	USROAccountsWebLibrary::Login(EmailTextBox->GetText().ToString(), PasswordTextBox->GetText().ToString(), Request);
}

void USROLoginWidget::Reset()
{
	PasswordTextBox->SetText(FText());
	LoginButton->SetIsEnabled(true);
}

void USROLoginWidget::OnSuccessfulLogin(FString AuthToken, int32 UserId) const
{
	ASROOfflineController* PC = Cast<ASROOfflineController>(GetPlayerContext().GetPlayerController());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get player controller"))
		return;
	}

	PC->AuthToken = AuthToken;
	PC->UserId = UserId;
	
	ASROLoginHUD* HUD = Cast<ASROLoginHUD>(PC->GetHUD());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get HUD"))
		return;
	}

	HUD->LoginCompleted();
}
