// Copyright 2022 Shattered Realms Online


#include "UI/Login/SROLoginHUD.h"

#include "Kismet/GameplayStatics.h"
#include "SRO/SRO.h"
#include "UI/Login/SROCreateCharacterWidget.h"
#include "UI/Login/SROLoginWidget.h"

ASROLoginHUD::ASROLoginHUD()
{
	static ConstructorHelpers::FClassFinder<USROLoginWidget> FoundLoginWidget(TEXT("/Game/SRO/Core/Login/Blueprints/BP_LoginWidget"));
	LoginWidgetClass = FoundLoginWidget.Class;
	
	static ConstructorHelpers::FClassFinder<USROCharacterSelectorWidget> FoundCharacterSelectorWidget(TEXT("/Game/SRO/Core/Login/Blueprints/BP_CharacterSelectorWidget"));
	CharacterSelectorWidgetClass = FoundCharacterSelectorWidget.Class; 
	
	static ConstructorHelpers::FClassFinder<USROCreateCharacterWidget> FoundCreateCharacterWidget(TEXT("/Game/SRO/Core/Login/Blueprints/BP_CreateCharacterWidget"));
	CreateCharacterWidgetClass = FoundCreateCharacterWidget.Class; 
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

	if (CreateCharacterWidgetClass)
	{
		CreateCharacterWidget = CreateWidget<USROCreateCharacterWidget>(GetWorld(), CreateCharacterWidgetClass);
		if (!CreateCharacterWidget)
		{
			UE_LOG(LogSRO, Warning, TEXT("Create Character Widget NOT created"));
		}
	}
	else
	{
		UE_LOG(LogSRO, Warning, TEXT("Create Character Widget Class NOT found"));
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
	if (LoginWidget->IsInViewport())
	{
		LoginWidget->RemoveFromViewport();
	}

	if (CreateCharacterWidget->IsInViewport())
	{
		CreateCharacterWidget->RemoveFromViewport();
	}

	if (!CharacterSelectorWidget->IsInViewport())
	{
		CharacterSelectorWidget->Reset();
		CharacterSelectorWidget->AddToViewport();
	}
}

void ASROLoginHUD::LogoutCompleted() const
{
	if (CharacterSelectorWidget->IsInViewport())
	{
		CharacterSelectorWidget->RemoveFromViewport();
	}

	if (CreateCharacterWidget->IsInViewport())
	{
		CreateCharacterWidget->RemoveFromViewport();
	}

	if (!LoginWidget->IsInViewport())
	{
		LoginWidget->Reset();
		LoginWidget->AddToViewport();
	}
}

void ASROLoginHUD::CreateCharacter() const
{
	if (CharacterSelectorWidget->IsInViewport())
	{
		CharacterSelectorWidget->RemoveFromViewport();
	}

	if (LoginWidget->IsInViewport())
	{
		LoginWidget->RemoveFromViewport();
	}

	if (!CreateCharacterWidget->IsInViewport())
	{
		CreateCharacterWidget->Reset();
		CreateCharacterWidget->AddToViewport();
	}
}
