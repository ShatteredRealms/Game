//ForeFront electronics 2021

#include "JWTPluginBPLibrary.h"
#include "JWTPlugin.h"

UJWTPluginBPLibrary::UJWTPluginBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

TMap<FString, FString> UJWTPluginBPLibrary::GetClaims(const FString& JWTToken)
{
	TMap<FString, FString> claims;
	if (JWTToken.IsEmpty()) 
		return claims;
	try {
		auto decoded = jwt::decode(TCHAR_TO_ANSI(*JWTToken));

		for (auto& Item : decoded.get_payload_claims())
		{
			FString value = Item.second.to_json().serialize().c_str();
			claims.Add(Item.first.c_str(), value.TrimQuotes());
		}
	}
	catch (...) {}
	return claims;
}

TMap<FString, FString> UJWTPluginBPLibrary::GetHeaderClaims(const FString& JWTToken)
{
	TMap<FString, FString> claims;
	if (JWTToken.IsEmpty()) 
		return claims;

	try
	{
		auto decoded = jwt::decode(TCHAR_TO_ANSI(*JWTToken));

		for (auto& Item : decoded.get_header_claims())
		{
			FString value = Item.second.to_json().serialize().c_str();
			claims.Add(Item.first.c_str(), value.TrimQuotes());
		}
	} catch(...) {}
	return claims;
}

UJWTVerifier* UJWTPluginBPLibrary::CreateVerifier(const FString& Key, EAlgorithm Algorithm)
{
	UJWTVerifier* jwtVerifier = NewObject<UJWTVerifier>();
	jwtVerifier->SetAlgorithm(Key, Algorithm);

	return jwtVerifier;
}

UJWTVerifier* UJWTPluginBPLibrary::CreateVerifier(const FString& Key, FString Algorithm)
{
	const auto alg = Algorithm.ToLower();

	if (alg.Equals("rs256"))
		return CreateVerifier(Key, EAlgorithm::rs256);

	if (alg.Equals("hs256"))
		return CreateVerifier(Key, EAlgorithm::hs256);

	if (alg.Equals("hs348"))
		return CreateVerifier(Key, EAlgorithm::hs384);

	if (alg.Equals("hs512"))
		return CreateVerifier(Key, EAlgorithm::hs512);

	if (alg.Equals("rs384"))
		return CreateVerifier(Key, EAlgorithm::rs384);

	if (alg.Equals("rs512"))
		return CreateVerifier(Key, EAlgorithm::rs512);

	return nullptr;
}

UJWTGenerator* UJWTPluginBPLibrary::CreateGenerator()
{

	UJWTGenerator* jwtGenerator = NewObject<UJWTGenerator>();

	return jwtGenerator;
}

