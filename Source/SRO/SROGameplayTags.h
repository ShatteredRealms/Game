// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "NativeGameplayTags.h"

namespace SROGameplayTags
{
	SRO_API FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);

	// Declare all of the custom native tags that SRO will use
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_IsDead);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_Cooldown);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_Cost);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_TagsBlocked);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_TagsMissing);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_Networking);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_ActivationGroup);

	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Behavior_SurvivesDeath);

	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Mouse);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Stick);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Crouch);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_AutoRun);

	// SRO_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_Spawned);
	// SRO_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_DataAvailable);
	// SRO_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_DataInitialized);
	// SRO_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_GameplayReady);

	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_Death);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_Reset);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_RequestReset);

	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Damage);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Heal);

	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cheat_GodMode);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cheat_UnlimitedHealth);

	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Crouching);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Fighting);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_AutoRunning);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death_Dying);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death_Dead);
	
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Combat_Weapon);

	// These are mappings from MovementMode enums to GameplayTags associated with those enums (below)
	SRO_API extern const TMap<uint8, FGameplayTag> MovementModeTagMap;
	SRO_API extern const TMap<uint8, FGameplayTag> CustomMovementModeTagMap;

	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Walking);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_NavWalking);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Falling);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Swimming);
	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Flying);

	SRO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Custom);
};
