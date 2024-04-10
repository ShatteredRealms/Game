// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SROWebLibrary.generated.h"

USTRUCT(BlueprintType)
struct FErrorResponse
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Message;
};

USTRUCT(BlueprintType)
struct FGenericResponse
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FErrorResponse Error;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Success;
};

/**
 * 
 */
UCLASS()
class SRO_API USROWebLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static FString GetGameBackendAPIUrl();
	
	UFUNCTION(BlueprintCallable)
	static FString GetCharactersAPIUrl();

	UFUNCTION(BlueprintCallable)
	static FString GetChatAPIUrl();

	/** Sets the necessary headers for a valid HTTP request and processes it. */
	static void ProcessJSONRequest(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request, const FString& URL, const FString& RequestType, const FString& Body);

	/** Sets the necessary headers for a valid HTTP request and processes it. */
	static void ProcessAuthRequest(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request, const FString& URL, const FString& RequestType, const FString& Body, const FString& AuthToken);

	/** Returns a string in case of an error, otherwise an empty string. */
	static FString ValidateResponse(const bool& bWasSuccessful, const FHttpResponsePtr& Response);
	
	/** Returns a string in case of an error. Otherwise returns an empty string and a valid JsonObject containing the JSON response. */
	static FString ValidateJsonResponse(const bool& bWasSuccessful, const FHttpResponsePtr& Response, TSharedPtr<FJsonObject>& JsonObject);

	/** Creates metadata with an authorization bearer token */
	static TMap<FString, FString> CreateAuthMetaData(FString AuthToken);
};
