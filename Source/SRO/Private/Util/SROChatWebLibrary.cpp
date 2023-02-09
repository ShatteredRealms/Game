#include "Util/SROChatWebLibrary.h"

#include "Util/SROWebLibrary.h"

void USROChatWebLibrary::SendChatMessage(const FText& Message, int64 ChannelId, FString AuthToken, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request)
{
	const FString Url = FString::Format(
		TEXT("{0}/message/channel/{1}"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<2>>
			{
				FStringFormatArg(USROWebLibrary::GetChatAPIUrl()),
				FStringFormatArg(ChannelId),
			}
		)
	);

	const FString Body = FString::Format(
		TEXT("{\"message\":\"{0}\"}"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<3>>
			{
				FStringFormatArg(Message.ToString()),
			}
		)
	);
	
	USROWebLibrary::ProcessAuthRequest(Request, Url, "POST", Body, AuthToken);	
}
