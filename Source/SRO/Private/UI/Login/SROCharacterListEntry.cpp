// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Login/SROCharacterListEntry.h"

#include "SRO/SRO.h"

USROCharacterListEntry::USROCharacterListEntry(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (Highlight)
	{
		Highlight->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USROCharacterListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	CharacterDetails= Cast<USROCharacterDetails>(ListItemObject);
	if (!CharacterDetails)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to cast list item to base character"))
	}
}

void USROCharacterListEntry::NativeOnItemSelectionChanged(bool bIsSelected)
{
	if (Highlight)
	{
		Highlight->SetVisibility(bIsSelected ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
	}
}
