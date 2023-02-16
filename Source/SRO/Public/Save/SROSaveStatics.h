// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SROSaveGame.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SRO/SROPlayerController.h"
#include "SROSaveStatics.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API USROSaveStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	static FString GetSlotName(ASROPlayerController* PC);

public:
	/**
	 * Gets the save game for a given player controller. If it does not exist, one is created.
	 * 
	 * @param PC Player controller to get save for
	 * @returns Save game for the Player Controller
	 */
	UFUNCTION(BlueprintCallable)
	static USROSaveGame* GetSaveGame(ASROPlayerController* PC);
	
	/**
	 * Save game for a given character name. If it does not exist, one is created.
	 * 
	 * @param PC Player controller to save settings for
	 * @returns True if the save game was successful
	 * 
	 * @TODO(Wil Simpson): Make async and have delegates for success/failure
	 */
	UFUNCTION(BlueprintCallable)
	static bool SaveGame(ASROPlayerController* PC);

	/**
	 * Resets the save game to default setup.
	 *
	 * @param PC Player controller to save settings for
	 * @returns True if the save game was successful
	 */
	UFUNCTION(BlueprintCallable)
	static bool ResetSaveGame(ASROPlayerController* PC);
};
