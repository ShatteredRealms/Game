// Copyright Shattered Realms Online All Rights Reserved


#include "Inventory/Equipment/SROEquipment.h"

#include "Inventory/Equipment/SROEquipmentInstance.h"

USROEquipment::USROEquipment(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	InstanceType = USROEquipmentInstance::StaticClass();
}
