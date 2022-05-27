// Copyright 2022 Shattered Realms Online


#include "UI/Login/SROLoginHUD.h"

ASROLoginHUD::ASROLoginHUD()
{
	static ConstructorHelpers::FClassFinder<USROLoginWidget> FoundLoginWidget(TEXT("/Game/Login/Blueprints/BP_LoginWidget"));
	LoginWidgetClass = FoundLoginWidget.Class; 
}

void ASROLoginHUD::BeginPlay()
{
	Super::BeginPlay();

	if (LoginWidgetClass)
	{
		UE_LOG(LogTemp, Log, TEXT("Found class"));
		LoginWidget = CreateWidget<USROLoginWidget>(GetWorld(), LoginWidgetClass);
		if (LoginWidget)
		{
			LoginWidget->AddToViewport();
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Class NOT found"));
	}
}

void ASROLoginHUD::Login() const
{
	if (LoginWidget)
	{
		LoginWidget->Login();
	}
}
