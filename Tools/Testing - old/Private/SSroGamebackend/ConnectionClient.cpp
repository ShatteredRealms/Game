//Generated by TurboLink CodeGenerator, do not edit!
#include "SSroGamebackend/ConnectionClient.h"
#include "SSroGamebackend/ConnectionService.h"
#include "ConnectionContext.h"
#include "TurboLinkGrpcManager_Private.h"
#include "Templates/SharedPointer.h"

FGrpcContextHandle UConnectionServiceClient::InitConnectGameServer()
{
	FGrpcContextHandle handle = Service->TurboLinkManager->GetNextContextHandle();
	auto context = UGrpcClient::MakeContext<GrpcContext_ConnectionService_ConnectGameServer>(handle);
	context->RpcContext = UTurboLinkGrpcManager::Private::CreateRpcClientContext();
	return context->GetHandle();
}

void UConnectionServiceClient::ConnectGameServer(FGrpcContextHandle Handle, const FGrpcSroCharactersCharacterTarget& Request)
{
	auto context = UGrpcClient::GetContext(Handle);
	if (context != nullptr)
	{
		auto contextConnectGameServer = StaticCastSharedPtr<GrpcContext_ConnectionService_ConnectGameServer>(*context);
		contextConnectGameServer->Call(Request);
	}
}
void UConnectionServiceClient::TryCancel(FGrpcContextHandle Handle)
{
	auto context = UGrpcClient::GetContext(Handle);
	if (context != nullptr)
	{
		(*context)->TryCancel();
	}
}

void UConnectionServiceClient::Shutdown()
{
	OnConnectGameServerResponse.Clear();
	Super::Shutdown();
}