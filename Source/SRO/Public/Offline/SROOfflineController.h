// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SROOfflineController.generated.h"


UCLASS(Blueprintable)
class SRO_API ASROOfflineController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};

