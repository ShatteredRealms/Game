// Copyright Shattered Realms Online All Rights Reserved


#include "Inventory/SROInventoryItem.h"

USROInventoryItem::USROInventoryItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const USROInventoryItemFragment* USROInventoryItem::FindFragmentByClass(
	TSubclassOf<USROInventoryItemFragment> FragmentClass) const
{
	if (FragmentClass != nullptr)
	{
		for (USROInventoryItemFragment* Fragment : Fragments)
		{
			if (Fragment && Fragment->IsA(FragmentClass))
			{
				return Fragment;
			}
		}
	}

	return nullptr;
}
