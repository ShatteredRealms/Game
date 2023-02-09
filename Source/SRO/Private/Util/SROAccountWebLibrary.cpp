// Copyright Shattered Realms Online All Rights Reserved


#include "Util/SROAccountsWebLibrary.h"
#include "Util/SROWebLibrary.h"

void USROAccountsWebLibrary::Login(const FString& Username, const FString& Password, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request)
{
	const FString Body = FString::Format(
		TEXT("{ \"username\":\"{0}\", \"password\":\"{1}\" }"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<2>>
			{
				FStringFormatArg(Username.TrimStartAndEnd()),
				FStringFormatArg(Password.TrimStartAndEnd())
			}));

	USROWebLibrary::ProcessJSONRequest(Request, USROWebLibrary::GetAccountsAPIUrl()+"/login", "POST", Body);	
}
