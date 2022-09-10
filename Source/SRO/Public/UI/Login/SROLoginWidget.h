// Copyright 2022 Shattered Realms Online

#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "SROLoginHUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "SROLoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API USROLoginWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	FHttpModule* Http;

public:
	USROLoginWidget(const class FObjectInitializer& ObjectInitializer);

	//+ Start Login Panel
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UCanvasPanel* LoginPanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UEditableTextBox* EmailTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UEditableTextBox* PasswordTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UTextBlock* LoginErrorText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UButton* LoginButton;

	UFUNCTION(BlueprintCallable, Category = "Login")
	void Login();

	UFUNCTION(BlueprintCallable, Category = "Login")
	void Reset();

	UFUNCTION(Category = "Login")
	void OnSuccessfulLogin(FString AuthToken, int32 UserId) const;

private:
	void OnLoginRequestReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
	void LoginFailed(const FString Message) const;
	//- Stop Login Panel
};
