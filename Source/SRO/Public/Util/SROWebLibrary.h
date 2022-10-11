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
	/** Gets the API URL for the backend server. The URL does NOT end in a forward slash. */
	UFUNCTION(BlueprintCallable)
	static FString GetAPIUrl();

	UFUNCTION(BlueprintCallable)
	static FString GetServerFinderURL();
	
	/** Processes a login request to the backend auth servers given a request. */
	static void Login(const FString& Username, const FString& Password, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request);

	/** Sets the necessary headers for a valid HTTP request and processes it. */
	static void ProcessJSONRequest(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request, const FString& URL, const FString& RequestType, const FString& Body);

	/** Sets the necessary headers for a valid HTTP request and processes it. */
	static void ProcessAuthRequest(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request, const FString& URL, const FString& RequestType, const FString& Body, const FString& AuthToken);

	/** Returns a string in case of an error, otherwise an empty string. */
	static FString ValidateResponse(const bool& bWasSuccessful, const FHttpResponsePtr& Response);
	
	/** Returns a string in case of an error. Otherwise returns an empty string and a valid JsonObject containing the JSON response. */
	static FString ValidateJsonResponse(const bool& bWasSuccessful, const FHttpResponsePtr& Response, TSharedPtr<FJsonObject>& JsonObject);
};
