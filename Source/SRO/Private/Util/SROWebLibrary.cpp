// Copyright Shattered Realms Online All Rights Reserved


#include "Util/SROWebLibrary.h"

#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Util/BackendSettings.h"

FString USROWebLibrary::GetAPIUrl()
{
	const UBackendSettings* Settings = GetDefault<UBackendSettings>();
	return Settings->APIUrl;
}

FString USROWebLibrary::GetGRPCAPIUrl()
{
	const UBackendSettings* Settings = GetDefault<UBackendSettings>();
	return Settings->GRPCAPIUrl;
}

FString USROWebLibrary::GetGameBackendAPIUrl()
{
#if UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
	return "localhost:8082/v1";
#else
	return GetAPIUrl()+"/gamebackend/v1";
#endif
}

FString USROWebLibrary::GetCharactersAPIUrl()
{
#if UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
	return "localhost:8081/v1";
#else
	return GetAPIUrl()+"/characters/v1";
#endif
}

FString USROWebLibrary::GetAccountsAPIUrl()
{
#if UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
	return "localhost:8080/v1";
#else
	return GetAPIUrl()+"/accounts/v1";
#endif
}

FString USROWebLibrary::GetChatAPIUrl()
{
#if UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
	return "localhost:8180/v1";
#else
	return GetAPIUrl()+"/chat/v1";
#endif
}

FString USROWebLibrary::GetChatGRPCUrl()
{
#if UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
	return "localhost:8180";
#else
	return "chat."+GetGRPCAPIUrl()+":8180";
#endif
}

void USROWebLibrary::ProcessJSONRequest(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request, const FString& URL,
                                        const FString& RequestType, const FString& Body)
{
	Request->SetURL(URL);
	Request->SetVerb(RequestType);
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
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
					FStringFormatArg(FString::FromInt(Response->GetResponseCode()))
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
