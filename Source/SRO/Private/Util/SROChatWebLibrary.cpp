#include "Util/SROChatWebLibrary.h"

#include "Chaos/AABB.h"
#include "Chaos/AABB.h"
#include "Util/SROWebLibrary.h"

void USROChatWebLibrary::SendChatMessage(const FString& CharacterName, const FText& Message, int64 ChannelId, FString AuthToken, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request)
{
	const FString Url = FString::Format(
		TEXT("{0}/message/channel/id/{1}"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<2>>
			{
				FStringFormatArg(USROWebLibrary::GetChatAPIUrl()),
				FStringFormatArg(ChannelId),
			}
		)
	);

	const FString Body = FString::Format(
		TEXT(R"({"chatMessage":{"message":"{0}","characterName":"{1}"}})"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<2>>
			{
				FStringFormatArg(Message.ToString()),
				FStringFormatArg(CharacterName),
			}
		)
	);
	
	USROWebLibrary::ProcessAuthRequest(Request, Url, "PUT", Body, AuthToken);	
}
