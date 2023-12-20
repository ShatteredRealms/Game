// Copyright Shattered Realms Online All Rights Reserved


#include "Inventory/SROInventoryItemInstance.h"

#include "Net/UnrealNetwork.h"

void USROInventoryItemInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(USROInventoryItemInstance, StackCount, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(USROInventoryItemInstance, BaseItem, COND_OwnerOnly);
}
