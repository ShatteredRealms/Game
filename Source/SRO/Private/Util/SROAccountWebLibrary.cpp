// Copyright Shattered Realms Online All Rights Reserved


#include "Util/SROAccountsWebLibrary.h"
#include "Util/SROWebLibrary.h"

void USROAccountsWebLibrary::Login(const FString& Email, const FString& Password, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request)
{
	const FString URL = USROWebLibrary::GetAPIUrl()+"/accounts/v1/login";
	const FString Body = FString::Format(
		TEXT("{ \"email\":\"{0}\", \"password\":\"{1}\" }"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<2>>
			{
				FStringFormatArg(Email.TrimStartAndEnd()),
				FStringFormatArg(Password.TrimStartAndEnd())
			}));

	USROWebLibrary::ProcessJSONRequest(Request, URL, "POST", Body);	
}
