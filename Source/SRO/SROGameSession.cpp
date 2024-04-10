// Copyright 2022 Shattered Realms Online


#include "SROGameSession.h"

#include "SRO.h"

ASROGameSession::ASROGameSession()
{
	const FString EnvAuthClientId = FPlatformMisc::GetEnvironmentVariable(TEXT("SRO_AUTH_CLIENT_ID"));
	const FString EnvAuthClientSecret = FPlatformMisc::GetEnvironmentVariable(TEXT("SRO_AUTH_CLIENT_SECRET"));

	if (!EnvAuthClientId.IsEmpty())
	{
		UE_LOG(LogSRO, Display, TEXT("Using AuthClientId from environment: %s"), *EnvAuthClientId);
		AuthClientId = EnvAuthClientId;
	}
	else
	{
		UE_LOG(LogSRO, Display, TEXT("Using default AuthClientId: %s"), *AuthClientId);
	}

	if (!EnvAuthClientSecret.IsEmpty())
	{
		UE_LOG(LogSRO, Display, TEXT("Using EnvAuthClientSecret	from environment: %s"), *EnvAuthClientSecret);
		AuthClientSecret = EnvAuthClientSecret;
	}
	else
	{
		UE_LOG(LogSRO, Display, TEXT("Using default AuthClientSecret: %s"), *AuthClientSecret);
	}
}
