// Copyright 2022 Shattered Realms Online


#include "UI/Login/SROLoginWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Offline/SROOfflineController.h"
#include "Offline/SROOfflineGameMode.h"
#include "Offline/SROOfflinePawn.h"
#include "SRO/SRO.h"
#include "SRO/SROGameInstance.h"
#include "SRO/SROGameMode.h"
#include "Util/SROWebLibrary.h"

USROLoginWidget::USROLoginWidget(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Http = &FHttpModule::Get();
}

void USROLoginWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (LoginThrobber)
	{
		LoginThrobber->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (LoginPanel)
	{	
		LoginPanel->SetVisibility(ESlateVisibility::Visible);
	}
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

	OnSuccessfulLogin(JsonObject->GetStringField("access_token"), JsonObject->GetStringField("refresh_token"));
}

void USROLoginWidget::LoginFailed(const FString Message) const
{
	LoginErrorText->SetVisibility(ESlateVisibility::Visible);
	LoginErrorText->SetText(FText::FromString(Message));
	PasswordTextBox->SetText(FText::FromString(TEXT("")));
	LoginButton->SetIsEnabled(true);
	LoginThrobber->SetVisibility(ESlateVisibility::Hidden);
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
	LoginThrobber->SetVisibility(ESlateVisibility::HitTestInvisible);

	const auto Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &USROLoginWidget::OnLoginRequestReceived);

	USROGameInstance* GI = Cast<USROGameInstance>(GetGameInstance());
	if (!GI)
	{
		UE_LOG(LogSRO, Error, TEXT("Invalid game instance"))
		return;
	}

	GI->Keycloak->Login(UsernameTextBox->GetText().ToString(), PasswordTextBox->GetText().ToString(), Request);
}

void USROLoginWidget::Reset()
{
	PasswordTextBox->SetText(FText());
	LoginButton->SetIsEnabled(true);
	LoginThrobber->SetVisibility(ESlateVisibility::Hidden);
}

void USROLoginWidget::OnSuccessfulLogin(FString AuthToken, FString RefreshToken) const
{
	USROGameInstance* GI = Cast<USROGameInstance>(GetGameInstance());
	if (!GI)
	{
		UE_LOG(LogSRO, Error, TEXT("Invalid game instance"))
		return;
	}

	GI->UpdateAuthTokens(AuthToken, RefreshToken);

	ASROOfflineController* PC = Cast<ASROOfflineController>(GetOwningPlayer());
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
