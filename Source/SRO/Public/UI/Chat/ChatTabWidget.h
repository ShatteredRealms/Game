// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ChatTabWidget.generated.h"


class SRO_API UChatTabWidget;

DECLARE_DELEGATE_OneParam(FChatTabSelectedDelegate, UChatTabWidget*)

/**
 * 
 */
UCLASS()
class SRO_API UChatTabWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	FChatTabSelectedDelegate* OnChatTabSelected;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chat", meta = (BindWidget))
	UButton* TabButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chat", meta = (BindWidget))
	UTextBlock* TabName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSelected;

	UFUNCTION()
	void OnTabClicked();
};
