// Copyright Shattered Realms Online All Rights Reserved


#include "UI/Login/SROCharacterSelectorWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Offline/SROOfflineController.h"
#include "SRO/SRO.h"
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
}

void USROCharacterSelectorWidget::Logout()
{
	ASROOfflineController* PC = Cast<ASROOfflineController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PC)
	{
		UE_LOG(LogSRO, Error, TEXT("Unable to get player controller"))
		return;
	}

	PC->AuthToken = nullptr;
	PC->UserId = -1;

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

	USROBaseCharacter* Character;
	for ( TSharedPtr<FJsonValue> CharacterJsonValue : JsonObject->GetArrayField("characters"))
	{
		Character = NewObject<USROBaseCharacter>();
		Character->BaseData = FSROBaseCharacterStruct(CharacterJsonValue->AsObject());
		CharacterList->AddItem(Character);
	}
	
	CharacterList->SetSelectedIndex(0);
}