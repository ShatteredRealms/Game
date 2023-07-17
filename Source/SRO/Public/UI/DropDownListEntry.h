// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DropDownData.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "DropDownListEntry.generated.h"


/**
 * 
 */
UCLASS()
class SRO_API UDropDownListEntry : public UUserWidget, public IUserObjectListEntry 
{
	GENERATED_BODY()

private:
	FSlateBrush OriginalStyle;
	FSlateBrush OriginalHoveredStyle;
	
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDropDownData* Data;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* EntryText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* Button;
	
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	
	UFUNCTION()
	void OnClicked();
	
	UFUNCTION()
	void OnSelected();

	UFUNCTION()
	void OnUnhovered();
};
