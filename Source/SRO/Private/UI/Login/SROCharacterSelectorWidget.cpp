// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Login/SROCharacterSelectorWidget.h"

#include "TurboLinkGrpcConfig.h"
#include "TurboLinkGrpcManager.h"
#include "TurboLinkGrpcUtilities.h"
#include "Gameplay/Character/SROCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Offline/SROOfflineController.h"
#include "SRO/SRO.h"
#include "SRO/SROGameInstance.h"
#include "SSroCharacter/CharacterService.h"
#include "SSroGamebackend/ConnectionService.h"
#include "UI/Login/SROLoginHUD.h"
#include "Util/SROWebLibrary.h"

void USROCharacterSelectorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	USROGameInstance* GI = Cast<USROGameInstance>(GetGameInstance());
	if (!GI)
	{
		UE_LOG(LogSRO, Error, TEXT("Invalid game instance"))
		return;
	}

	auto TLM = UTurboLinkGrpcUtilities::GetTurboLinkGrpcManager(GetWorld());
	if (!TLM)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to load TurboLink GRPC Utilities"));
		return;
	}

	auto CharacterService = Cast<UCharacterService>(TLM->MakeService("CharacterService"));
	if (!CharacterService)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to create character service"));
		return;
	}
	CharacterServiceClient = CharacterService->MakeClient();
	CharacterServiceClient->OnGetCharactersResponse.AddUniqueDynamic(this, &USROCharacterSelectorWidget::OnGetCharactersReceived);
	CharacterService->Connect();
	
	const auto Handle = CharacterServiceClient->InitGetCharacters();
	TMap<FString, FString> MetaData = USROWebLibrary::CreateAuthMetaData(GI->AuthToken);
	CharacterServiceClient->GetCharacters(Handle, FGrpcGoogleProtobufEmpty(), MetaData);

	auto ConnectionService = Cast<UConnectionService>(TLM->MakeService("ConnectionService"));
	if (!ConnectionService)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to create connection service"));
		return;
	}
	ConnectionServiceClient = ConnectionService->MakeClient();
	ConnectionServiceClient->OnConnectGameServerResponse.AddUniqueDynamic(this, &USROCharacterSelectorWidget::OnConnectResponseReceived);
	ConnectionService->Connect();
	
	SelectedCharacterSpawnLocation = {0, 0, 0};
	SelectedCharacterSpawnRotator = {0, 0, 0};
	BaseActorClass = ASROCharacter::StaticClass();
	PlayThrobber->SetVisibility(ESlateVisibility::Hidden);
}

void USROCharacterSelectorWidget::Logout()
{

	USROGameInstance* GI = Cast<USROGameInstance>(GetGameInstance());
	if (!GI)
	{
		UE_LOG(LogSRO, Error, TEXT("Invalid game instance"))
		return;
	}

	GI->Logout();
	
	ASROOfflineController* PC = Cast<ASROOfflineController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get player controller"))
		return;
	}

	ASROLoginHUD* HUD = Cast<ASROLoginHUD>(PC->GetHUD());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get HUD"))
		return;
	}

	HUD->LogoutCompleted();
}

void USROCharacterSelectorWidget::Reset()
{
	CharacterList->ClearListItems();
	ErrorText->SetText(FText());
}

void USROCharacterSelectorWidget::CreateCharacter()
{
	ASROOfflineController* PC = Cast<ASROOfflineController>(GetPlayerContext().GetPlayerController());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get player controller"))
		return;
	}

	ASROLoginHUD* HUD = Cast<ASROLoginHUD>(PC->GetHUD());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get HUD"))
		return;
	}

	HUD->CreateCharacter();
}

void USROCharacterSelectorWidget::Play()
{
	USROGameInstance* GI = Cast<USROGameInstance>(GetGameInstance());
	if (!GI)
	{
		UE_LOG(LogSRO, Error, TEXT("Invalid game instance"))
		return;
	}

	USROCharacterDetails* Character = CharacterList->GetSelectedItem<USROCharacterDetails>();
	if (!Character)
	{
		UE_LOG(LogSRO, Error, TEXT("No character selected"))
		return;
	}

	const auto Handle = ConnectionServiceClient->InitConnectGameServer();
	FGrpcSroCharacterCharacterTarget Request;
	Request.Type.Id = Character->GRPCData.Id;
	Request.Type.TypeCase = EGrpcSroCharacterCharacterTargetType::Id;
	TMap<FString, FString> MetaData = USROWebLibrary::CreateAuthMetaData(GI->AuthToken);
	ConnectionServiceClient->ConnectGameServer(Handle, Request, MetaData);
	
	PlayThrobber->SetVisibility(ESlateVisibility::HitTestInvisible);
	PlayButton->SetIsEnabled(false);
	ErrorText->SetVisibility(ESlateVisibility::Hidden);
}

void USROCharacterSelectorWidget::OnConnectResponseReceived(
	FGrpcContextHandle Handle,
	const FGrpcResult& GrpcResult,
	const FGrpcSroGamebackendConnectGameServerResponse& Response)
{
	PlayThrobber->SetVisibility(ESlateVisibility::Hidden);
	PlayButton->SetIsEnabled(true);

	if (GrpcResult.Code != EGrpcResultCode::Ok)
	{
		if (GrpcResult.Message.IsEmpty())
		{
			ErrorText->SetText(FText::FromString(TEXT("An error occurred")));
		}
		else
		{
			ErrorText->SetText(FText::FromString(GrpcResult.Message));
		}
		ErrorText->SetText(FText::FromString(GrpcResult.Message));
		ErrorText->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	
	ASROOfflineController* PC = Cast<ASROOfflineController>(GetOwningPlayer());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get player controller"))
		return;
	}
	
	USROGameInstance* GI = Cast<USROGameInstance>(GetGameInstance());
	if (!GI)
	{
		UE_LOG(LogSRO, Error, TEXT("Invalid game instance"))
		return;
	}

	USROCharacterDetails* Character = CharacterList->GetSelectedItem<USROCharacterDetails>();
	if (!Character)
	{
		UE_LOG(LogSRO, Error, TEXT("No character selected"))
		return;
	}

	FString URL = FString::Format(
		TEXT("{0}:{1}?t={2}"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<4>>
			{
				FStringFormatArg(Response.Address),
				FStringFormatArg(Response.Port),
				FStringFormatArg(Response.ConnectionId),
			}));

	GI->SelectedCharacterName = Character->GRPCData.Name;
	GI->SelectedCharacterId = Character->GRPCData.Id;
	GI->ChatManager->OnConnectedAllChannels().BindWeakLambda(this, [PC, URL]
	{
		PC->ClientTravel(URL, TRAVEL_Absolute);
	});
	
	GI->ChatManager->ConnectAllChannels();
}

void USROCharacterSelectorWidget::OnGetCharactersReceived(
	FGrpcContextHandle Handle,
	const FGrpcResult& GrpcResult,
	const FGrpcSroCharacterCharactersDetails& Response)
{
	for (auto CharacterData : Response.Characters)
	{
		USROCharacterDetails* Character = NewObject<USROCharacterDetails>();
		Character->GRPCData = CharacterData;
		CharacterList->AddItem(Character);
	}
}
