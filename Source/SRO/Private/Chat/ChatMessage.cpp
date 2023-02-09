#include "Chat/ChatMessage.h"

FString UChatMessage::GenerateText()
{
	return FString::Printf(TEXT("%s: %s"), *ChatMessage.Username, *ChatMessage.Message);
}
