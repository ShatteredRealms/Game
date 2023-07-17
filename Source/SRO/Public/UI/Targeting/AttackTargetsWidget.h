// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AttackTargetWidget.h"
#include "Blueprint/UserWidget.h"
#include "AttackTargetsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API UAttackTargetsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UAttackTargetWidget* AttackTargetWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UAttackTargetWidget* FightingTargetWidget;
	
	UFUNCTION(BlueprintCallable)
	void SetAttackTarget(AFightingTarget* NewTarget);
	
	UFUNCTION(BlueprintCallable)
	void SetFightingTarget(AFightingTarget* NewTarget);
};
