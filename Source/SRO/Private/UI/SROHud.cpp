// Copyright Shattered Realms Online All Rights Reserved


#include "UI/SROHud.h"

#include "Save/SROSaveStatics.h"
#include "UI/SROBaseUI.h"

ASROHud::ASROHud()
{
	static ConstructorHelpers::FClassFinder<USROBaseUI> FoundBaseUIClass(TEXT("/Game/SRO/Core/UI/BP_BaseUI"));
	BaseUIClass = FoundBaseUIClass.Class;
}

void ASROHud::BeginPlay()
{
	Super::BeginPlay();

	if (BaseUIClass)
	{
		BaseUI = CreateWidget<USROBaseUI>(GetWorld(), BaseUIClass);
		if (BaseUI)
		{
			BaseUI->AddToViewport();
		}
	}
}
