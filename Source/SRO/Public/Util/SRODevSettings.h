// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SRODevSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Developer Settings"))
class SRO_API USRODevSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/**
	 * Development builds ONLY.
	 *
	 * If set along with TestPassword, then will automatically sign-in as this user
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Auth")
	FText TestUserUsername;
	
	/**
	 * Development builds ONLY.
	 *
	 * If set along with TestUsername, then will automatically sign-in as this user
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Auth")
	FText TestUserPassword;

	/**
	 * The development keycloak realm name
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString KeycloakDevRealmName = "default";
	
	/**
	 * The development keycloak client id
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString KeycloakDevClientId = "sro-gameclient";
	
	/**
	 * The development keycloak host
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString KeycloakDevHost = "http://localhost:8080";
	
	/**
	 * The production keycloak realm name
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString KeycloakProdRealmName = "default";
	
	/**
	 * The production keycloak client id
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString KeycloakProdClientId = "sro-gameclient";
	
	/**
	 * The production keycloak host
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString KeycloakProdHost = "https://sso.shatteredrealmsonline.com";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auth")
	FString AuthServerClientId = "a0adc9ef-dc42-406a-8de4-b9ae70cb2e61";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auth")
	FString AuthServerClientSecret;

	/** Gets the keycloak realm name depending on the build configuration (ie- development or shipping) */
	UFUNCTION(BlueprintCallable)
	FString GetKeycloakRealmName() const;

	/** Gets the keycloak client id depending on the build configuration (ie- development or shipping) */
	UFUNCTION(BlueprintCallable)
	FString GetKeycloakClientId() const;

	/** Gets the keycloak host depending on the build configuration (ie- development or shipping) */
	UFUNCTION(BlueprintCallable)
	FString GetKeycloakHost() const;
};
