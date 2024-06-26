//Generated by TurboLink CodeGenerator, do not edit!
#pragma once
#include "TurboLinkGrpcService.h"
#include "SSroCharacters/CharactersClient.h"
#include "CharactersService.generated.h"

class UTurboLinkGrpcManager;

UCLASS(ClassGroup = TurboLink, BlueprintType)
class TURBOLINKGRPC_API UCharactersService : public UGrpcService
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void Connect() override;
	
	UFUNCTION(BlueprintCallable)
	virtual EGrpcServiceState GetServiceState() const override;

	UFUNCTION(BlueprintCallable)
	UCharactersServiceClient* MakeClient();

private:
	virtual void Shutdown() override;

	UPROPERTY()
	UCharactersServiceClient* InnerClient; 
public:
	typedef TFunction<void(const FGrpcResult& GrpcResult, const FGrpcSroCharactersGenders& Response)> FGetGendersLambda;
	void CallGetGenders(const FGrpcGoogleProtobufEmpty& Request, FGetGendersLambda Lambda);

	typedef TFunction<void(const FGrpcResult& GrpcResult, const FGrpcSroCharactersRealms& Response)> FGetRealmsLambda;
	void CallGetRealms(const FGrpcGoogleProtobufEmpty& Request, FGetRealmsLambda Lambda);

	typedef TFunction<void(const FGrpcResult& GrpcResult, const FGrpcSroCharactersCharactersResponse& Response)> FGetCharactersLambda;
	void CallGetCharacters(const FGrpcGoogleProtobufEmpty& Request, FGetCharactersLambda Lambda);

	typedef TFunction<void(const FGrpcResult& GrpcResult, const FGrpcSroCharactersCharacterResponse& Response)> FGetCharacterLambda;
	void CallGetCharacter(const FGrpcSroCharactersCharacterTarget& Request, FGetCharacterLambda Lambda);

	typedef TFunction<void(const FGrpcResult& GrpcResult, const FGrpcSroCharactersCharacterResponse& Response)> FCreateCharacterLambda;
	void CallCreateCharacter(const FGrpcSroCharactersCreateCharacterRequest& Request, FCreateCharacterLambda Lambda);

	typedef TFunction<void(const FGrpcResult& GrpcResult, const FGrpcGoogleProtobufEmpty& Response)> FDeleteCharacterLambda;
	void CallDeleteCharacter(const FGrpcSroCharactersCharacterTarget& Request, FDeleteCharacterLambda Lambda);

	typedef TFunction<void(const FGrpcResult& GrpcResult, const FGrpcSroCharactersCharactersResponse& Response)> FGetAllCharactersForUserLambda;
	void CallGetAllCharactersForUser(const FGrpcSroUserTarget& Request, FGetAllCharactersForUserLambda Lambda);

	typedef TFunction<void(const FGrpcResult& GrpcResult, const FGrpcGoogleProtobufEmpty& Response)> FEditCharacterLambda;
	void CallEditCharacter(const FGrpcSroCharactersEditCharacterRequest& Request, FEditCharacterLambda Lambda);

	typedef TFunction<void(const FGrpcResult& GrpcResult, const FGrpcSroCharactersPlayTimeResponse& Response)> FAddCharacterPlayTimeLambda;
	void CallAddCharacterPlayTime(const FGrpcSroCharactersAddPlayTimeRequest& Request, FAddCharacterPlayTimeLambda Lambda);

public:
	class Private;
	Private* const d = nullptr;

public:
	UCharactersService();
	virtual ~UCharactersService();
};

