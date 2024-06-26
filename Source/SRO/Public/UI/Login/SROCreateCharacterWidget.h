// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Interfaces/IHttpRequest.h"
#include "SROCreateCharacterWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS(Blueprintable)
class SRO_API USROCreateCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	FHttpModule* Http;
	
public:
	virtual void NativeConstruct() override;

// Navigation Buttons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UButton* CreateButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UButton* LogoutButton;

// Output information
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UEditableTextBox* NameTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UTextBlock* ErrorText;

// Button functions
	UFUNCTION(BlueprintCallable)
	void Reset();
	
	UFUNCTION(BlueprintCallable)
	void CreateCharacter();
	
	UFUNCTION(BlueprintCallable)
	void Cancel();

	UFUNCTION(BlueprintCallable)
	void Logout();

private:	
	void OnCreateCharacterResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
