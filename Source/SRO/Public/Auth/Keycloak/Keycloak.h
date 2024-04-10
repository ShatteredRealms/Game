// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "JWTVerifier.h"
#include "Interfaces/IHttpRequest.h"
#include "UObject/Object.h"
#include "Keycloak.generated.h"


/**
 * SRO API endpoints
 */
UENUM(BlueprintType)
enum EEndpoint
{
	WellKnown,
	Authorization,
	Token,
	UserInfo,
	Logout,
	Certificate,
	Introspection,
	TokenRevocation,
};

/**
 * JWT key structure used for SRO auth
 */
USTRUCT(BlueprintType)
struct FJWTKey
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString kid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString kty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString alg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString use;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString n;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString e;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> x5c;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString x5t;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ProcessedKey;

	FJWTKey() {};

	FJWTKey( FString _kid, FString _kty, FString _alg, FString _use, FString _n, FString _e, TArray<FString> _x5c, FString _x5t){
		kid = _kid;
		kty = _kty;
		alg = _alg;
		use = _use;
		n = _n;
		e = _e;
		x5c = _x5c;
		x5t = _x5t;
	}
};

/**
 * JWK used for JWT auth. Essentially a list of JWT keys.
 */
USTRUCT(BlueprintType)
struct FJWK
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FJWTKey> keys;

	FJWK() {};

	FJWK( TArray<FJWTKey> _keys ){
		keys = _keys;
	}
};

// DECLARE_DYNAMIC_DELEGATE(FKeycloakAdapterFinishedDelegate);
// DECLARE_DYNAMIC_DELEGATE_OneParam(FKeycloakAdapterErrorDelegate, const FString&, Error);
// DECLARE_DYNAMIC_DELEGATE_TwoParams(FKeycloakAdapterRefreshAuthTokenDelegate, const FString&, AuthToken, const FString&, RefreshToken);

DECLARE_DELEGATE(FKeycloakAdapterFinishedDelegate);
DECLARE_DELEGATE_OneParam(FKeycloakAdapterErrorDelegate, const FString& Error);
DECLARE_DELEGATE_TwoParams(FKeycloakAdapterRefreshAuthTokenDelegate, const FString& AuthToken, const FString& RefreshToken);
/**
 * 
 */
UCLASS(Blueprintable, Config=Game)
class SRO_API UKeycloak : public UObject
{
	GENERATED_BODY()

protected:
	/** All valid JWT keys */
	TMap<FString, FJWTKey> JWTKeys;

	/** Called when an error occurs within keycloak */
	FKeycloakAdapterErrorDelegate ErrorDelegate;

	/** Called when JWK is refreshed */
	FKeycloakAdapterFinishedDelegate JWKRefreshedDelegate;

	/** Called with auth token is refreshed */
	FKeycloakAdapterRefreshAuthTokenDelegate RefreshAuthTokenDelegate;
	
public:
	/**
	 * The development keycloak realm name
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	FString Realm = "default";
	
	/**
	 * The development keycloak client id
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	FString ClientId = "sro-gameclient";
	
	/**
	 * The development keycloak host
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	FString Host = "http://localhost:8080";

	/**
	 * Gets the fully qualified API endpoint given the endpoint enum
	 * @return fully qualified API endpoint
	 */
	UFUNCTION(BlueprintCallable)
	FString GetEndpointUrl(EEndpoint Endpoint) const;

	/**
	 * Request to get latest JWKs
	 */
	void UpdateJWKs();

	/**
	 * Validates whether the given token is valid and signed correctly.
	 * @returns empty string on success, otherwise an error message
	 */
	UFUNCTION(BlueprintCallable)
	FString ValidateToken(FString& Token) const;

	/**
	 * Requests a new token, given a refresh token. If an error occurs, the ErrorDelegate is broadcasted with an error,
	 * message, otherwise the success delegate is broadcasted with the new auth token.
	 */
	void RefreshAuthToken(FString& RefreshToken) const;

	/** Requests to login using the given username and password given an HTTP request. */
	void Login(const FString& Username, const FString& Password, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request) const;

	/** Request to login as an OAuth client given an id and secret given an HTTP request. */
	void ClientLogin(const FString& Id, const FString Secret, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request);

	/** Gets the JWK refresh delegate */
	FKeycloakAdapterFinishedDelegate& OnJWKRefreshed() { return JWKRefreshedDelegate; }

	/** Gets the keycloak error delegate */
	FKeycloakAdapterErrorDelegate& OnKeycloakError() { return ErrorDelegate; }
	
	/** Gets the refresh auth token delegate */
	FKeycloakAdapterRefreshAuthTokenDelegate& OnRefreshAuthToken() { return RefreshAuthTokenDelegate; }

private:
	/** Called when UpdateJWKs response is received */
	void OnCompletedJWKRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, const bool bSucceeded);
};
