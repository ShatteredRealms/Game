// Copyright 2022 Shattered Realms Online


#include "UI/Login/SROLoginHUD.h"

void ASROLoginHUD::BeginPlay()
{
	Super::BeginPlay();

	if (LoginWidgetClass)
	{
		LoginWidget = CreateWidget<USROLoginWidget>(GetWorld(), LoginWidgetClass);
		if (LoginWidget)
		{
			LoginWidget->AddToViewport();
		}
	}
}

void ASROLoginHUD::Login() const
{
	if (LoginWidget)
	{
		LoginWidget->Login();
	}
}
