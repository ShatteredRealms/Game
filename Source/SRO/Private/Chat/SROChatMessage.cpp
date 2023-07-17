#include "Chat/SROChatMessage.h"

FString UChatMessage::GenerateText()
{
	return FString::Printf(TEXT("[%s] %s: %s"), *ChatChannelData.Name, *ChatMessage.CharacterName, *ChatMessage.Message);
}
