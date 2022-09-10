// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "SROCharacterSelectorWidget.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API USROCharacterSelectorWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	FHttpModule* Http;
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UButton* PlayButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UButton* LogoutButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UButton* CreateCharacterButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UListView* CharacterList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UTextBlock* ErrorText;

	UFUNCTION(BlueprintCallable)
	void Logout();
	
	UFUNCTION(BlueprintCallable)
	void Reset();
	
private:
	void OnCharactersReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
