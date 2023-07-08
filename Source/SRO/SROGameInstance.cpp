// Copyright 2022 Shattered Realms Online


#include "SROGameInstance.h"

#include "SRO.h"
#include "SROPlayerController.h"
#include "Save/SROSaveStatics.h"

void USROGameInstance::Init()
{
	Super::Init();
	
	ChatManager = NewObject<USROChatManager>();
	ChatManager->InitService(this);
	Keycloak = NewObject<UKeycloak>();
	Keycloak->OnKeycloakError().BindUObject(this, &USROGameInstance::OnKeycloakError);
	Keycloak->OnRefreshAuthToken().BindUObject(this, &USROGameInstance::UpdateAuthTokens);
	Keycloak->UpdateJWKs();

	GetTimerManager().SetTimer(
		TokenRefreshTimerHandle,
		this,
		&USROGameInstance::RequestUpdateTokens,
		60.f,
		true,
		60.f);
}

void USROGameInstance::Logout()
{
	AuthToken.Empty();
	RefreshToken.Empty();
	UserId.Empty();
	AccountUsername.Empty();
	ChatManager->Disconnect();
}

void USROGameInstance::OnKeycloakError(const FString& Error)
{
	UE_LOG(LogSRO, Warning, TEXT("Keycloak ERROR: %s"), *Error);
}

void USROGameInstance::UpdateAuthTokens(const FString& NewAuthToken, const FString& NewRefreshToken)
{
	// TODO(wil): Validate auth token
	AuthToken = NewAuthToken;
	RefreshToken = NewRefreshToken;

	TArray<FString> Partitions;
	if (AuthToken.ParseIntoArray(Partitions, TEXT(".")) == 3)
	{
		FString Claims;
		FBase64::Decode(Partitions[1], Claims);
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Claims);
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			UserId = JsonObject->GetStringField("sub");
			AccountUsername = JsonObject->GetStringField("preferred_username");
		}
		else
		{
			UE_LOG(LogSRO, Error, TEXT("Unable to parse user id"))
		}
	}
	else
	{
		UE_LOG(LogSRO, Error, TEXT("Invalid Auth Token"));
	}
}

void USROGameInstance::RequestUpdateTokens()
{
	if (!RefreshToken.IsEmpty())
	{
		UE_LOG(LogSRO, Display, TEXT("Requesting new auth tokens"));
		Keycloak->RefreshAuthToken(RefreshToken);
	}
}
