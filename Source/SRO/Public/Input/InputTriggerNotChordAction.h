// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "InputTriggerNotChordAction.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Not Chorded Action", NotInputConfigurable = "true"))
class SRO_API UInputTriggerNotChordAction : public UInputTriggerChordAction
{
	GENERATED_BODY()

protected:
	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;
};
