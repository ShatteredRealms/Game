// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Chat/ChatMessageListEntry.h"

#include "SRO/SRO.h"

void UChatMessageListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	ChatMessage = Cast<UChatMessage>(ListItemObject);
	if (!ChatMessage)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to cast list item to chat message"))
		return;
	}

	// CharacterNameText->SetText(FText::FromString(ChatMessage->ChatMessage.CharacterName));
	// MessageText->SetText(FText::FromString(ChatMessage->ChatMessage.Message));
	// ChannelNameText->SetText(FText::FromString(ChatMessage->ChatChannelData.Name));

	MessageText->SetText(FText::FromString(FString::Printf(
		TEXT("[%s] %s: %s"),
		*ChatMessage->ChatChannelData.Name,
		*ChatMessage->ChatMessage.CharacterName,
		*ChatMessage->ChatMessage.Message)));
}

void UChatMessageListEntry::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}
