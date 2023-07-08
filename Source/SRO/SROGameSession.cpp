// Copyright 2022 Shattered Realms Online


#include "SROGameSession.h"

FString ASROGameSession::GetAuthClientId()
{
#if UE_BUILD_DEVELOPMENT
	return AuthClientIdDev;
#else
	return AuthClientIdProd;
#endif
}

FString ASROGameSession::GetAuthClientSecret()
{
#if UE_BUILD_DEVELOPMENT
	return AuthClientSecretDev;
#else
	return AuthClientSecretProd;
#endif
}
