// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Chat/ChatMessageListEntry.h"

#include "SRO/SRO.h"

void UChatMessageListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	ChatMessage = Cast<UChatMessage>(ListItemObject);
	if (!ChatMessage)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to cast list item to chat message"))
	}
	MessageText->SetText(FText::FromString(ChatMessage->GenerateText()));
}

void UChatMessageListEntry::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}
