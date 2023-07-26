// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "GameFramework/Target.h"
#include "TargetDetailsWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SRO_API UTargetDetailsWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	ATarget* Target;

	UPROPERTY()
	bool bTargeted;

	UPROPERTY()
	bool bFightingTargeted;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* TargetNameText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* FactionNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* HealthBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	USizeBox* HealthSizeBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UBorder* Border;

	UFUNCTION(BlueprintCallable)
	void Setup(ATarget* NewTarget);

	UFUNCTION(BlueprintCallable)
	void UpdateHealthBarSize();

	UFUNCTION(BlueprintCallable)
	void UpdateHealthPercentage();

	UFUNCTION(BlueprintCallable)
	void UpdateTargetName();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ATarget* GetTarget() { return Target; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetTargeted(bool bNewTargeted);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetFightingTarget(bool bNewFightingTargeted);
};
