// Copyright Shattered Realms Online All Rights Reserved


#include "Util/SROCharactersWebLibrary.h"

#include "Util/SROWebLibrary.h"

FString USROCharactersWebLibrary::CharactersURL()
{
	return USROWebLibrary::GetAPIUrl()+"/characters/v1";
}

void USROCharactersWebLibrary::Connect(int32 CharacterId, FString AuthToken,
                                       TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request)
{
	const FString Url = FString::Format(
		TEXT("{0}/connect/{1}"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<2>>
			{
				FStringFormatArg(USROWebLibrary::GetAPIUrl()+"/gamebackend/v1"),
				FStringFormatArg(CharacterId),
			}
		)
	);
	
	USROWebLibrary::ProcessAuthRequest(Request, Url, "GET", "", AuthToken);	
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

void USROCharactersWebLibrary::CreateCharacter(TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request, FString AuthToken,
	int32 OwnerId, FString Name, int32 GenderId, int32 RealmId)
{
	const FString Url = FString::Format(
		TEXT("{0}/users/{1}/characters"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<2>>
			{
				FStringFormatArg(CharactersURL()),
				FStringFormatArg(OwnerId),
			}
		)
	);
	
	const FString Body = FString::Format(
		TEXT("{\"name\":\"{0}\",\"gender\":{1},\"realm\":{2}}"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<3>>
			{
				FStringFormatArg(Name),
				FStringFormatArg(GenderId),
				FStringFormatArg(RealmId),
			}
		)
	);
	
	USROWebLibrary::ProcessAuthRequest(Request, Url, "POST", Body, AuthToken);	
}
