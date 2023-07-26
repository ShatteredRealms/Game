// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameFramework/FightingTarget.h"
#include "AttackTargetWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SRO_API UAttackTargetWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	AFightingTarget* Target;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* TargetNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* HealthBar;
	
	UFUNCTION(BlueprintCallable)
	void SetTarget(AFightingTarget* NewTarget);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AFightingTarget* GetTarget() { return Target; }

	UFUNCTION(BlueprintImplementableEvent)
	void TargetUpdated();
};
