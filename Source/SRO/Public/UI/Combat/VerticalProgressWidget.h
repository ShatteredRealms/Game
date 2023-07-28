// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "UI/MoveableWidget.h"
#include "VerticalProgressWidget.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API UVerticalProgressWidget : public UMoveableWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* ProgressBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	USizeBox* SizeBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FLinearColor FillColor;
	
public:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetFillPercent(float NewPercent);
};
