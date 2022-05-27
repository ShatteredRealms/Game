// Copyright 2022 Shattered Realms Online


#include "UI/Login/SROLoginWidget.h"

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
				"Invalid username and password" : Message+" while logging in";

		LoginFailed(ErrorMessage);
		return;
	}

	AuthToken = JsonObject->GetStringField("token");
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
	if (UsernameTextBox->GetText().ToString() == "")
	{
		LoginFailed("Username cannot be empty");
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

	USROAccountsWebLibrary::Login(UsernameTextBox->GetText().ToString(), PasswordTextBox->GetText().ToString(), Request);
}