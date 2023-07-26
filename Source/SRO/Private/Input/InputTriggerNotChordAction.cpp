// Copyright Shattered Realms Online All Rights Reserved


#include "Input/InputTriggerNotChordAction.h"
#include "EnhancedPlayerInput.h"

#include "InputAction.h"

ETriggerState UInputTriggerNotChordAction::UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput,
                                                                      FInputActionValue ModifiedValue, float DeltaTime)
{
	const FInputActionInstance* EventData = PlayerInput->FindActionInstanceData(ChordAction);
	
	return EventData && EventData->GetValue().IsNonZero() ? ETriggerState::None : ETriggerState::Triggered;
}
