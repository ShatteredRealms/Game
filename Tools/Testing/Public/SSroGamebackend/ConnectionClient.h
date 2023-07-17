//Generated by TurboLink CodeGenerator, do not edit!
#pragma once
#include "TurboLinkGrpcClient.h"
#include "SSroGamebackend/ConnectionMessage.h"
#include "ConnectionClient.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnConnectionServiceConnectGameServerResponse, FGrpcContextHandle, Handle, const FGrpcResult&, GrpcResult, const FGrpcSroGamebackendConnectGameServerResponse&, Response);

UCLASS(ClassGroup = TurboLink, BlueprintType)
class TURBOLINKGRPC_API UConnectionServiceClient : public UGrpcClient
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnConnectionServiceConnectGameServerResponse OnConnectGameServerResponse;

public:
	UFUNCTION(BlueprintCallable)
	FGrpcContextHandle InitConnectGameServer();

	UFUNCTION(BlueprintCallable)
	void ConnectGameServer(FGrpcContextHandle Handle, const FGrpcSroCharactersCharacterTarget& Request);

public:
	virtual void Shutdown() override;

	UFUNCTION(BlueprintCallable)
	void TryCancel(FGrpcContextHandle Handle);
};
