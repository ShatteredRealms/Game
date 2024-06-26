//Generated by TurboLink CodeGenerator, do not edit!
#include "SSro/HealthService.h"
#include "SSro/HealthClient.h"
#include "HealthService_Private.h"
#include "HealthMarshaling.h"
#include "TurboLinkGrpcManager_Private.h"
#include "TurboLinkGrpcUtilities.h"

UHealthService::UHealthService()
	: d(new UHealthService::Private())
{
}

UHealthService::~UHealthService()
{
	delete d;
}

void UHealthService::Connect()
{
	FString serviceEndPoint = UTurboLinkGrpcUtilities::GetTurboLinkGrpcConfig()->GetServiceEndPoint(TEXT("HealthService"));
	UE_LOG(LogTurboLink, Warning, TEXT("Connect to HealthService: '%s'"), *serviceEndPoint);

	if (d->Channel == nullptr) {
		d->Channel = TurboLinkManager->d->CreateServiceChannel(TCHAR_TO_UTF8(*serviceEndPoint), this);
	}
	if (d->Stub == nullptr) {
		d->Stub = sro::HealthService::NewStub(d->Channel->RpcChannel);
	}

	grpc_connectivity_state currentChannelState = d->Channel->RpcChannel->GetState(true);
	if (OnServiceStateChanged.IsBound())
	{
		OnServiceStateChanged.Broadcast(UTurboLinkGrpcManager::Private::GrpcStateToServiceState(currentChannelState));
	}
}

EGrpcServiceState UHealthService::GetServiceState() const
{
	if (d->Channel == nullptr) return EGrpcServiceState::NotCreate;

	auto rpcChannelState = d->Channel->RpcChannel->GetState(false);
	return UTurboLinkGrpcManager::Private::GrpcStateToServiceState(rpcChannelState);
}

UHealthServiceClient* UHealthService::MakeClient()
{
	auto client = UGrpcService::MakeClient<UHealthServiceClient>();
	return client;
}

void UHealthService::Shutdown()
{
	Super::Shutdown();
	d->Stub = nullptr;
	if (d->Channel != nullptr) {
		TurboLinkManager->d->RemoveServiceChannel(d->Channel, this);
		d->Channel = nullptr;
	}
}

void UHealthService::CallHealth(const FGrpcGoogleProtobufEmpty& Request, FHealthLambda Lambda)
{
	if (InnerClient == nullptr)
	{
		InnerClient = MakeClient();
	}
	UHealthServiceHealthLambdaWrapper* lambdaWrapper = NewObject<UHealthServiceHealthLambdaWrapper>();
	lambdaWrapper->InnerClient = InnerClient;
	lambdaWrapper->Lambda = Lambda;
	lambdaWrapper->Handle = InnerClient->InitHealth();
	InnerClient->OnHealthResponse.AddUniqueDynamic(lambdaWrapper, &UHealthServiceHealthLambdaWrapper::OnResponse);
	InnerClient->Health(lambdaWrapper->Handle, Request);
}
