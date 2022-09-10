// Copyright 2022 Shattered Realms Online


#include "UI/Login/SROLoginHUD.h"

#include "Kismet/GameplayStatics.h"
#include "SRO/SRO.h"
#include "UI/Login/SROLoginWidget.h"

ASROLoginHUD::ASROLoginHUD()
{
	static ConstructorHelpers::FClassFinder<USROLoginWidget> FoundLoginWidget(TEXT("/Game/Login/Blueprints/BP_LoginWidget"));
	LoginWidgetClass = FoundLoginWidget.Class;
	
	static ConstructorHelpers::FClassFinder<USROCharacterSelectorWidget> FoundCharacterSelectorWidget(TEXT("/Game/Login/Blueprints/BP_CharacterSelectorWidget"));
	CharacterSelectorWidgetClass = FoundCharacterSelectorWidget.Class; 
}

void ASROLoginHUD::BeginPlay()
{
	Super::BeginPlay();

	if (LoginWidgetClass)
	{
		LoginWidget = CreateWidget<USROLoginWidget>(GetWorld(), LoginWidgetClass);
		if (LoginWidget)
		{
			LoginWidget->AddToViewport();
			UE_LOG(LogSRO, Display, TEXT("Login Widget Added to view"));
		}
		else
		{
			UE_LOG(LogSRO, Warning, TEXT("Login Widget NOT created"));
		}
	}
	else
	{
		UE_LOG(LogSRO, Warning, TEXT("Login Widget Class NOT found"));
	}

	if (CharacterSelectorWidgetClass)
	{
		CharacterSelectorWidget = CreateWidget<USROCharacterSelectorWidget>(GetWorld(), CharacterSelectorWidgetClass);
		if (!CharacterSelectorWidget)
		{
			UE_LOG(LogSRO, Warning, TEXT("Character Select Widget NOT created"));
		}
	}
	else
	{
		UE_LOG(LogSRO, Warning, TEXT("Character Select Widget Class NOT found"));
	}

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
}

void ASROLoginHUD::Login() const
{
	if (LoginWidget)
	{
		LoginWidget->Login();
	}
}

void ASROLoginHUD::LoginCompleted() const
{
	LoginWidget->RemoveFromViewport();
	CharacterSelectorWidget->Reset();
	CharacterSelectorWidget->AddToViewport();
}

void ASROLoginHUD::LogoutCompleted() const
{
	CharacterSelectorWidget->RemoveFromViewport();
	LoginWidget->Reset();
	LoginWidget->AddToViewport();
}
