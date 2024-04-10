// Copyright Shattered Realms Online All Rights Reserved


#include "Util/SROWebLibrary.h"

#include "Auth/Keycloak/Keycloak.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Util/BackendSettings.h"

FString USROWebLibrary::GetGameBackendAPIUrl()
{
	const UBackendSettings* BackendSettings = GetDefault<UBackendSettings>();
	return BackendSettings->GameBackendHTTPUrl;
}

FString USROWebLibrary::GetCharactersAPIUrl()
{
	const UBackendSettings* BackendSettings = GetDefault<UBackendSettings>();
	return BackendSettings->CharacterHTTPUrl;
}

FString USROWebLibrary::GetChatAPIUrl()
{
	const UBackendSettings* BackendSettings = GetDefault<UBackendSettings>();
	return BackendSettings->ChatHTTPUrl;
}

void USROWebLibrary::ProcessJSONRequest(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request, const FString& URL,
                                        const FString& RequestType, const FString& Body)
{
	Request->SetURL(URL);
	Request->SetVerb(RequestType);
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetTimeout(10);
	if (Body != "") Request->SetContentAsString(Body);
	Request->ProcessRequest();
}

void USROWebLibrary::ProcessAuthRequest(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request, const FString& URL,
	const FString& RequestType, const FString& Body, const FString& AuthToken)
{
	const FString Authorization = FString::Format(
		TEXT("Bearer {0}"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<1>>
			{
				FStringFormatArg(AuthToken),
			}
		)
	);
	
	Request->SetHeader(TEXT("Authorization"), Authorization);
	
	ProcessJSONRequest(Request, URL, RequestType, Body);
}


FString USROWebLibrary::ValidateResponse(const bool& bWasSuccessful, const FHttpResponsePtr& Response)
{
	if (!(bWasSuccessful && Response.IsValid()))
	{
		return TEXT("Server returned invalid response");	
	}
	
	if (!EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		return FString::Format(TEXT("Error {0}"),
			static_cast<FStringFormatOrderedArguments>(
				TArray<FStringFormatArg, TFixedAllocator<1>>{
					FStringFormatArg(FString::FromInt(Response->GetResponseCode())),
				}
			)
		);
	}
	
	return TEXT("");;
}

FString USROWebLibrary::ValidateJsonResponse(const bool& bWasSuccessful, const FHttpResponsePtr& Response,
                                            TSharedPtr<FJsonObject>& JsonObject)
{
	if (const FString Message = ValidateResponse(bWasSuccessful, Response); Message != TEXT(""))
	{
		return Message;
	}
	
	TSharedPtr<FJsonObject> OutObject;
	if (const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		!FJsonSerializer::Deserialize(Reader, OutObject))
	{
		return TEXT("Server returned invalid data");
	}
	
	JsonObject = OutObject.ToSharedRef();
	return TEXT("");;
}

TMap<FString, FString> USROWebLibrary::CreateAuthMetaData(FString AuthToken)
{
	TMap<FString, FString> MetaData = {{"authorization", FString::Format(TEXT("Bearer {0}"), { AuthToken })}};
	return MetaData;
}
