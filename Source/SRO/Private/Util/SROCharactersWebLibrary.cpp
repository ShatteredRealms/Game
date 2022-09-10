// Copyright Shattered Realms Online All Rights Reserved


#include "Util/SROCharactersWebLibrary.h"

#include "Util/SROWebLibrary.h"

FString USROCharactersWebLibrary::CharactersURL()
{
	return USROWebLibrary::GetAPIUrl()+"/characters/v1";
}

void USROCharactersWebLibrary::GetCharacters(int32 UserId, FString AuthToken, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request)
{
	const FString Url = FString::Format(
		TEXT("{0}/users/{1}/characters"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<2>>
			{
				FStringFormatArg(CharactersURL()),
				FStringFormatArg(UserId),
			}
		)
	);
	USROWebLibrary::ProcessAuthRequest(Request, Url, "GET", "", AuthToken);	
}
