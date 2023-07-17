// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DropDownListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "DropDownList.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SRO_API UDropDownList : public UUserWidget
{
	GENERATED_BODY()

public:
	UDropDownList(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UListView* Entries;

	UFUNCTION(BlueprintCallable)
	UDropDownData* CreateEntry(FString Name);
	UFUNCTION(BlueprintCallable)
	UDropDownData* AddEntry(UDropDownData* Data);

	UFUNCTION(BlueprintCallable)
	void SelectNext();
	
	UFUNCTION(BlueprintCallable)
	void SelectPrevious();
	
	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;

	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UFUNCTION()
	void Clear();

	UFUNCTION()
	void OnDropDownHovered(UDropDownData* SelectedData);
	
protected:
	UFUNCTION(BlueprintCallable)
	int32 GetSelectedIndex();
	
private:
	bool AnyButtonsHovered();
	
};

