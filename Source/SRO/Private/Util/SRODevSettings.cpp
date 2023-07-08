// Copyright Shattered Realms Online All Rights Reserved


#include "Util/SRODevSettings.h"

FString USRODevSettings::GetKeycloakRealmName() const
{
#if UE_BUILD_DEVELOPMENT
	return KeycloakDevRealmName;
#else
	return KeycloakProdRealmName;
#endif
}

FString USRODevSettings::GetKeycloakClientId() const
{
#if UE_BUILD_DEVELOPMENT
	return KeycloakDevClientId;
#else
	return KeycloakProdClientId;
#endif
}

FString USRODevSettings::GetKeycloakHost() const
{
#if UE_BUILD_DEVELOPMENT
	return KeycloakDevHost;
#else
	return KeycloakProdHost;
#endif
}
