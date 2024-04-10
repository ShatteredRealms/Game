// Copyright Shattered Realms Online All Rights Reserved


#include "Util/SROCharactersWebLibrary.h"

#include "SRO/SRO.h"
#include "Util/SROWebLibrary.h"

void USROCharactersWebLibrary::Connect(int32 CharacterId, FString AuthToken,
                                       TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request)
{
	const FString Url = FString::Format(
		TEXT("{0}/connect/character/id/{1}"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<2>>
			{
				FStringFormatArg(USROWebLibrary::GetGameBackendAPIUrl()),
				FStringFormatArg(CharacterId),
			}
		)
	);

	USROWebLibrary::ProcessAuthRequest(Request, Url, "GET", "", AuthToken);	
}

void USROCharactersWebLibrary::GetCharacters(FString UserId, FString AuthToken, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request)
{
	const FString Url = FString::Format(
		TEXT("{0}/users/id/{1}/characters"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<2>>
			{
				FStringFormatArg(USROWebLibrary::GetCharactersAPIUrl()),
				FStringFormatArg(UserId),
			}
		)
	);
	
	USROWebLibrary::ProcessAuthRequest(Request, Url, "GET", "", AuthToken);	
}

void USROCharactersWebLibrary::CreateCharacter(TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request, FString AuthToken,
	FString OwnerId, FString Name, FString Gender, FString Realm, FString Dimension)
{
	const FString Url = FString::Format(
		TEXT("{0}/users/id/{1}/characters"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<2>>
			{
				FStringFormatArg(USROWebLibrary::GetCharactersAPIUrl()),
				FStringFormatArg(OwnerId),
			}
		)
	);
	
	const FString Body = FString::Format(
		TEXT("{\"name\":\"{0}\",\"gender\":\"{1}\",\"realm\":\"{2}\",\"dimension\":{\"name\":\"{3}\"}}"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<4>>
			{
				FStringFormatArg(Name),
				FStringFormatArg(Gender),
				FStringFormatArg(Realm),
				FStringFormatArg(Dimension),
			}
		)
	);
	
	USROWebLibrary::ProcessAuthRequest(Request, Url, "POST", Body, AuthToken);	
}
