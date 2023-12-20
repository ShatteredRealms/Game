// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EEquipSlot
{
	NONE,
	
	// Weapon
	Weapon_Util1,
	Weapon_Util2,
	Weapon_Util3,
	Weapon_Util4,
	Weapon_Util5,
	Weapon_Util6,
	Weapon_RightHand,
	Weapon_Belt,
	Weapon_LeftHand,
	Weapon_BeltSlot1,
	Weapon_BeltSlot2,
	Weapon_BeltSlot3,
	Weapon_BeltSlot4,
	Weapon_BeltSlot5,
	Weapon_BeltSlot6,

	// Armor
	Armor_Neck,
	Armor_Head,
	Armor_Back,
	Armor_RightShoulder,
	Armor_Chest,
	Armor_LeftShoulder,
	Armor_RightArm,
	Armor_Hands,
	Armor_LeftArm,
	Armor_RightWrist,
	Armor_Legs,
	Armor_LeftWrist,
	Armor_RightHand,
	Armor_Feet,
	Armor_LeftHand,

	// Augments
	Augments_Eyes,
	Augments_Brain,
	Augments_Ears,
	Augments_RightShoulder,
	Augments_Chest,
	Augments_LeftShoulder,
	Augments_RightArm,
	Augments_Waist,
	Augments_LeftArm,
	Augments_RightWrist,
	Augments_Legs,
	Augments_LeftWrist,
	Augments_RightHand,
	Augments_Feet,
	Augments_LeftHand,
};
#include "Inventory/SROInventoryItem.h"
#include "IIF_Equippable.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API UIIF_Equippable : public USROInventoryItemFragment
{
	GENERATED_BODY()
	
};
