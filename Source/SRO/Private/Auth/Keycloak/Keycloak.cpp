// Copyright Shattered Realms Online All Rights Reserved


#include "Auth/Keycloak/Keycloak.h"

#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "JWTPluginBPLibrary.h"
#include "../../../../../Source/SRO/SRO.h"
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"
#include "Interfaces/IHttpResponse.h"
#include "Util/SRODevSettings.h"

FString UKeycloak::GetEndpointUrl(EEndpoint Endpoint) const
{
	const USRODevSettings* DevSettings = GetDefault<USRODevSettings>();
	switch (Endpoint) {
	case WellKnown:
			return FString::Format(
				TEXT("/realms/{0}/.well-known/openid-configuration"),
				FStringFormatOrderedArguments({
					FStringFormatArg(DevSettings->GetKeycloakRealmName()),
				})
			); 
		
		case Authorization:
			return FString::Format(
				TEXT("/realms/{0}/protocol/openid-connect/auth"),
				FStringFormatOrderedArguments({
					FStringFormatArg(DevSettings->GetKeycloakRealmName()),
				})
			); 
		
		case Token:
			return FString::Format(
				TEXT("/realms/{0}/protocol/openid-connect/token"),
				FStringFormatOrderedArguments({
					FStringFormatArg(DevSettings->GetKeycloakRealmName()),
				})
			); 
		
		case UserInfo:
			return FString::Format(
				TEXT("/realms/{0}/protocol/openid-connect/userinfo"),
				FStringFormatOrderedArguments({
					FStringFormatArg(DevSettings->GetKeycloakRealmName()),
				})
			); 
		
		case Logout:
			return FString::Format(
				TEXT("/realms/{0}/protocol/openid-connect/logout"),
				FStringFormatOrderedArguments({
					FStringFormatArg(DevSettings->GetKeycloakRealmName()),
				})
			); 
		
		case Certificate:
			return FString::Format(
				TEXT("/realms/{0}/protocol/openid-connect/certs"),
				FStringFormatOrderedArguments({
					FStringFormatArg(DevSettings->GetKeycloakRealmName()),
				})
			); 
		
		case Introspection:
			return FString::Format(
				TEXT("/realms/{0}/protocol/openid-connect/token/introspect"),
				FStringFormatOrderedArguments({
					FStringFormatArg(DevSettings->GetKeycloakRealmName()),
				})
			); 
		
		case TokenRevocation:
			return FString::Format(
				TEXT("/realms/{0}/protocol/openid-connect/token/revoke"),
				FStringFormatOrderedArguments({
					FStringFormatArg(DevSettings->GetKeycloakRealmName()),
				})
			);
		
		default:
			return "/EndpointNotDefinded";
	}
}

void UKeycloak::UpdateJWKs()
{
	FHttpModule* Http = &FHttpModule::Get();
	FHttpRequestRef Request = Http->CreateRequest();
	const USRODevSettings* DevSettings = GetDefault<USRODevSettings>();
	Request->SetURL(DevSettings->GetKeycloakHost()+GetEndpointUrl(Certificate));
	UE_LOG(LogSRO, Display, TEXT("Endpoint: %s"), *Request->GetURL());
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	Request->OnProcessRequestComplete().BindUObject(this, &UKeycloak::OnCompletedJWKRequest);
	if (!Request->ProcessRequest())
	{
		UE_LOG(LogSRO, Warning, TEXT("Unable to process keycloak request"))
	}
}

FString UKeycloak::ValidateToken(FString& Token) const
{
	const auto claims = UJWTPluginBPLibrary::GetHeaderClaims(Token);
	const auto kid = claims.Find("kid");
	if (kid == nullptr)
	{
		return "no kid in header";
	}
	
	auto key = JWTKeys.Find(*kid);
	if (key)
	{
		return UJWTPluginBPLibrary::CreateVerifier(key->ProcessedKey, key->alg)->VerifyJWT(Token)
			? ""
			: "invalid token";
	}

	
	return FString::Printf(TEXT("no cert for kid(%s)"), **kid);
}

void UKeycloak::RefreshAuthToken(FString& RefreshToken) const
{
	
	FHttpModule* Http = &FHttpModule::Get();
	FHttpRequestRef Request = Http->CreateRequest();
	const USRODevSettings* DevSettings = GetDefault<USRODevSettings>();
	Request->SetURL(DevSettings->GetKeycloakHost()+GetEndpointUrl(Certificate));
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("x-www-form-urlencoded"));
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	Request->SetContentAsString(FString::Format(
		TEXT("client_id={0}&grant_type=refresh_token&refresh_token={2}"),
		FStringFormatOrderedArguments({
			DevSettings->GetKeycloakClientId(),
			RefreshToken,
		})
	));
	Request->OnProcessRequestComplete().BindWeakLambda(this, [this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, const bool bSucceeded)
	{
		if (!bSucceeded)
		{
			ErrorDelegate.ExecuteIfBound("Unsuccessful Call");
			return;
		}

		FString Json = HttpResponse->GetContentAsString();
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
		if (!FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			ErrorDelegate.ExecuteIfBound(FString::Format(
				TEXT("Failed to parse response: {0}"),
				FStringFormatOrderedArguments({
					FStringFormatArg(HttpResponse->GetContentAsString()),
				})
			));
			return;
		}

		const auto newToken = JsonObject->GetStringField("access_token");
		if (newToken == "")
		{
			ErrorDelegate.ExecuteIfBound(FString::Format(
				TEXT("No access token in response: {0}"),
				FStringFormatOrderedArguments({
					FStringFormatArg(HttpResponse->GetContentAsString()),
				})
			));
			return;
		}
		
		const auto refreshToken = JsonObject->GetStringField("refresh_token");
		if (refreshToken == "")
		{
			ErrorDelegate.ExecuteIfBound(FString::Format(
				TEXT("No refresh token in response: {0}"),
				FStringFormatOrderedArguments({
					FStringFormatArg(HttpResponse->GetContentAsString()),
				})
			));
			return;
		}

		RefreshAuthTokenDelegate.ExecuteIfBound(newToken, refreshToken);
	});
}

void UKeycloak::Login(const FString& Username, const FString& Password,
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request) const
{
	const USRODevSettings* DevSettings = GetDefault<USRODevSettings>();
	Request->SetURL(DevSettings->GetKeycloakHost()+GetEndpointUrl(Token));
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	Request->SetContentAsString(FString::Format(
		TEXT("client_id={0}&username={1}&password={2}&grant_type=password"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<3>>
			{
				FStringFormatArg(DevSettings->GetKeycloakClientId()),
				FStringFormatArg(Username.TrimStartAndEnd()),
				FStringFormatArg(Password.TrimStartAndEnd()),
			})
	));

	Request->ProcessRequest();
}

void UKeycloak::ClientLogin(const FString& Id, const FString Secret, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request)
{
	const USRODevSettings* DevSettings = GetDefault<USRODevSettings>();
	Request->SetURL(DevSettings->GetKeycloakHost()+GetEndpointUrl(Token));
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	Request->SetContentAsString(FString::Format(
		TEXT("client_id={0}&client_secret={1}&grant_type=client_credentials"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<3>>
			{
				FStringFormatArg(Id),
				FStringFormatArg(Secret),
			})
	));

	Request->ProcessRequest();
}

void UKeycloak::OnCompletedJWKRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, const bool bSucceeded)
{
	if (!bSucceeded)
	{
		ErrorDelegate.ExecuteIfBound("Unsuccessful Call");
		return;
	}

	FString Json = Response->GetContentAsString();
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		ErrorDelegate.ExecuteIfBound(FString::Format(
			TEXT("Failed to parse response: {0}"),
			FStringFormatOrderedArguments({
				FStringFormatArg(Response->GetContentAsString()),
			})
		));
		return;
	}

	FJWK JWK;
	if (!FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &JWK, 0, 0))
	{
		ErrorDelegate.ExecuteIfBound("Failed to deserialize");
		return;
	}

	for (int idx=0; idx<JWK.keys.Num(); idx++)
	{
		FJWTKey key = JWK.keys[idx];
		FString pubKey = UTF8_TO_TCHAR(jwt::helper::convert_base64_der_to_pem(TCHAR_TO_UTF8(*key.x5c[0])).c_str());
		key.ProcessedKey = pubKey;
		JWTKeys.Add(key.kid, key);
	} // for loop

	JWKRefreshedDelegate.ExecuteIfBound();
}
