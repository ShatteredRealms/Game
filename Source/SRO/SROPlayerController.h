// Copyright 2022 Shattered Realms Online

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FightingTarget.h"
#include "Offline/SROOfflineController.h"
#include "UI/SROHud.h"
#include "SROPlayerController.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class SRO_API ASROPlayerController : public ASROOfflineController
{
	GENERATED_BODY()

private:
	/** Current target */
	UPROPERTY()
	ATarget* CurrentTarget;
	
public:
	ASROPlayerController();
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void PreDisconnect();

	/** Handle inputs */
	virtual bool InputKey(const FInputKeyParams& Params) override;
	
	UFUNCTION(BlueprintCallable, Category=Combat)
	void StartAttack();

	UFUNCTION(BlueprintCallable, Category=Combat)
	void EndAttack();

	UFUNCTION(BlueprintCallable, Category=Targetin)
	void ClearTarget();
	
	UFUNCTION(BlueprintCallable, Category=Targeting)
	void SetTarget(ATarget* NewTarget);

	/** Blueprint event to tell attack target updated */
	UFUNCTION(BlueprintImplementableEvent)
	void CurrentTargetUpdated();
	
	/** Blueprint event to tell fight target updated */
	UFUNCTION(BlueprintImplementableEvent)
	void FightTargetUpdated();

	virtual void OnPossess(APawn* InPawn) override;
	
private:
	// HELPER FUNCTIONS
	void UpdateTargetUI();
	void UpdateAttackTargetUI();
	void UpdateFightingTargetUI();
	// END HELPER FUNCTIONS
};


