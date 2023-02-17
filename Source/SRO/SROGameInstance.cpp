// Copyright 2022 Shattered Realms Online


#include "SROGameInstance.h"

#include "SROPlayerController.h"

void USROGameInstance::Shutdown()
{
	auto BPC = GetPrimaryPlayerController();
	if (BPC)
	{
		auto PC = Cast<ASROPlayerController>(BPC);
		if (PC)
		{
			PC->GetChatService()->Shutdown();
		}
	}
	
	Super::Shutdown();
}
