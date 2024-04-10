//Generated by TurboLink CodeGenerator, do not edit!
#include "SSroGamebackend/ConnectionNode.h"
#include "SSroGamebackend/ConnectionService.h"
#include "TurboLinkGrpcManager.h"
#include "TurboLinkGrpcUtilities.h"

UCallConnectionServiceConnectGameServer* UCallConnectionServiceConnectGameServer::ConnectGameServer(UObject* WorldContextObject, const FGrpcSroCharactersCharacterTarget& Request)
{
	UCallConnectionServiceConnectGameServer* node = NewObject<UCallConnectionServiceConnectGameServer>(WorldContextObject);
	UTurboLinkGrpcManager* turboLinkManager = UTurboLinkGrpcUtilities::GetTurboLinkGrpcManager(WorldContextObject);

	node->ConnectionService = Cast<UConnectionService>(turboLinkManager->MakeService("ConnectionService"));
	if (node->ConnectionService == nullptr)
	{
		return nullptr;
	}
	node->Request = Request;

	node->ConnectionService->OnServiceStateChanged.AddUniqueDynamic(node, &UCallConnectionServiceConnectGameServer::OnServiceStateChanged);
	WorldContextObject->GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda([node]() {
		node->ConnectionService->Connect();
	}));
	return node;
}

void UCallConnectionServiceConnectGameServer::OnServiceStateChanged(EGrpcServiceState NewState)
{
	if (NewState == EGrpcServiceState::TransientFailure)
	{
		FGrpcResult result;
		result.Code = EGrpcResultCode::ConnectionFailed;

		FGrpcSroGamebackendConnectGameServerResponse response;
		OnFail.Broadcast(result, response);

		Shutdown();
		return;
	}

	if (NewState == EGrpcServiceState::Ready)
	{
		ConnectionServiceClient = ConnectionService->MakeClient();
		ConnectionServiceClient->OnContextStateChange.AddUniqueDynamic(this, &UCallConnectionServiceConnectGameServer::OnContextStateChange);
		ConnectionServiceClient->OnConnectGameServerResponse.AddUniqueDynamic(this, &UCallConnectionServiceConnectGameServer::OnResponse);

		Context = ConnectionServiceClient->InitConnectGameServer();
		ConnectionServiceClient->ConnectGameServer(Context, Request);
	}
}

void UCallConnectionServiceConnectGameServer::OnContextStateChange(FGrpcContextHandle Handle, EGrpcContextState State)
{
	if (State == EGrpcContextState::Done)
	{
		Shutdown();
	}
}

void UCallConnectionServiceConnectGameServer::OnResponse(FGrpcContextHandle Handle, const FGrpcResult& GrpcResult, const FGrpcSroGamebackendConnectGameServerResponse& Response)
{
	if (GrpcResult.Code == EGrpcResultCode::Ok)
	{
		OnSuccess.Broadcast(GrpcResult, Response);
	}
	else
	{
		OnFail.Broadcast(GrpcResult, Response);
	}
}

void UCallConnectionServiceConnectGameServer::Shutdown()
{
	ConnectionService->OnServiceStateChanged.RemoveDynamic(this, &UCallConnectionServiceConnectGameServer::OnServiceStateChanged);
	if (ConnectionServiceClient != nullptr)
	{
		ConnectionService->RemoveClient(ConnectionServiceClient);
		ConnectionServiceClient->Shutdown();
		ConnectionServiceClient = nullptr;
	}

	if (ConnectionService != nullptr)
	{
		UTurboLinkGrpcUtilities::GetTurboLinkGrpcManager(this)->ReleaseService(ConnectionService);
		ConnectionService = nullptr;
	}

	SetReadyToDestroy();
#if ENGINE_MAJOR_VERSION>=5
	MarkAsGarbage();
#else
	MarkPendingKill();
#endif
}