// Copyright Shattered Realms Online All Rights Reserved


#include "Util/SROAccountsWebLibrary.h"
#include "Util/SROWebLibrary.h"

FString USROAccountsWebLibrary::AccountsURL()
{
	return USROWebLibrary::GetAPIUrl()+"/accounts/v1";
}

void USROAccountsWebLibrary::Login(const FString& Email, const FString& Password, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request)
{
	const FString Body = FString::Format(
		TEXT("{ \"email\":\"{0}\", \"password\":\"{1}\" }"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<2>>
			{
				FStringFormatArg(Email.TrimStartAndEnd()),
				FStringFormatArg(Password.TrimStartAndEnd())
			}));

	USROWebLibrary::ProcessJSONRequest(Request, AccountsURL()+"/login", "POST", Body);	
}
