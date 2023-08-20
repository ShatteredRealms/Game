// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
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
	AActor* Target;

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
	void Setup(AActor* NewTarget);

	UFUNCTION(BlueprintCallable)
	void SetDisplayName(FString NewDisplayName);

	UFUNCTION(BlueprintCallable)
	void UpdateHealthBarSize(float MaxHealth);

	UFUNCTION(BlueprintCallable)
	void UpdateHealthPercentage(float CurrentHealth, float MaxHealth);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetTargeted(bool bNewTargeted);
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsTargeted() { return bTargeted; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetAttacked(bool bNewFightingTargeted);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsAttacked() { return bFightingTargeted; }
};
