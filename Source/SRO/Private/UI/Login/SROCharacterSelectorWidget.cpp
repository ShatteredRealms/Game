// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Login/SROCharacterSelectorWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Offline/SROOfflineController.h"
#include "SRO/SRO.h"
#include "SRO/SROCharacter.h"
#include "UI/Login/SROLoginHUD.h"
#include "Util/SROCharactersWebLibrary.h"
#include "Util/SROWebLibrary.h"

void USROCharacterSelectorWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Http = &FHttpModule::Get();
	
	const auto Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &USROCharacterSelectorWidget::OnCharactersReceived);

	ASROOfflineController* PC = Cast<ASROOfflineController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get player controller"))
		return;
	}
	
	USROCharactersWebLibrary::GetCharacters(PC->UserId, PC->AuthToken, Request);

	SelectedCharacterSpawnLocation = {0, 0, 0};
	SelectedCharacterSpawnRotator = {0, 0, 0};

	BaseActorClass = ASROCharacter::StaticClass();
}

void USROCharacterSelectorWidget::Logout()
{
	ASROOfflineController* PC = Cast<ASROOfflineController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get player controller"))
		return;
	}

	PC->Logout();
	
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
	ASROOfflineController* PC = Cast<ASROOfflineController>(GetPlayerContext().GetPlayerController());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get player controller"))
		return;
	}

	USROBaseCharacter* Character = CharacterList->GetSelectedItem<USROBaseCharacter>();
	if (!Character)
	{
		UE_LOG(LogSRO, Error, TEXT("No character selected"))
		return;
	}
	
	const auto Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &USROCharacterSelectorWidget::OnConnectResponseReceived);
	USROCharactersWebLibrary::Connect(Character->BaseData.Id, PC->AuthToken, Request);
}

void USROCharacterSelectorWidget::OnCharactersReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                                       bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	const FString Message = USROWebLibrary::ValidateJsonResponse(bWasSuccessful, Response, JsonObject); 
	if (Message != TEXT(""))
	{
		ErrorText->SetText(FText::FromString(Message));
		ErrorText->SetVisibility(ESlateVisibility::Visible);
		return;
	}

	for ( TSharedPtr<FJsonValue> CharacterJsonValue : JsonObject->GetArrayField("characters"))
	{
		USROBaseCharacter* Character = NewObject<USROBaseCharacter>();
		Character->BaseData = FSROBaseCharacterStruct(CharacterJsonValue->AsObject());
		CharacterList->AddItem(Character);
	}
	
	CharacterList->SetSelectedIndex(0);
}
void USROCharacterSelectorWidget::OnConnectResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	const FString Message = USROWebLibrary::ValidateJsonResponse(bWasSuccessful, Response, JsonObject); 
	if (Message != TEXT(""))
	{
		ErrorText->SetText(FText::FromString(Message));
		ErrorText->SetVisibility(ESlateVisibility::Visible);
		return;
	}

	ASROOfflineController* PC = Cast<ASROOfflineController>(GetPlayerContext().GetPlayerController());
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get player controller"))
		return;
	}

	USROBaseCharacter* Character = CharacterList->GetSelectedItem<USROBaseCharacter>();
	if (!Character)
	{
		UE_LOG(LogSRO, Error, TEXT("No character selected"))
		return;
	}
	
	FString URL = FString::Format(
		TEXT("{0}:{1}?t={2}?c={3}"),
		static_cast<FStringFormatOrderedArguments>(
			TArray<FStringFormatArg, TFixedAllocator<4>>
			{
				FStringFormatArg(JsonObject->GetStringField("address")),
				FStringFormatArg(JsonObject->GetStringField("port")),
				FStringFormatArg(PC->AuthToken),
				FStringFormatArg(Character->BaseData.Name),
			}));
	
	GetPlayerContext().GetPlayerController()->ClientTravel(URL, TRAVEL_Absolute);
}
