#include "Chat/SROChatMessage.h"

FString UChatMessage::GenerateText()
{
	return FString::Printf(TEXT("%s: %s"), *ChatMessage.CharacterName, *ChatMessage.Message);
}
