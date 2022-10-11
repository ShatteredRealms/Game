// Copyright Shattered Realms Online All Rights Reserved


#include "Util/SROWebLibrary.h"

#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Util/BackendSettings.h"

void USROWebLibrary::Login(const FString& Username, const FString& Password, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request)
{
	const FString URL = GetAPIUrl()+"/v1/auth/login";
	const FString Body = FString::Format(
		TEXT("{ \"username\":\"{0}\", \"password\":\"{1}\" }"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<2>>
			{
				FStringFormatArg(Username.TrimStartAndEnd()),
				FStringFormatArg(Password.TrimStartAndEnd())
			}));

	ProcessJSONRequest(Request, URL, "POST", Body);	
}

FString USROWebLibrary::GetAPIUrl()
{
	const UBackendSettings* Settings = GetDefault<UBackendSettings>();
	return Settings->APIUrl;
}

FString USROWebLibrary::GetServerFinderURL()
{
#if UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
	return "127.0.0.1:8083/v1";
#else
	return USROWebLibrary::GetAPIUrl()+"/serverfinder/v1/";
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
