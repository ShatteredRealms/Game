// Copyright 2022 Shattered Realms Online

#pragma once

#include "CoreMinimal.h"
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
	AActor* CurrentTarget;

	UPROPERTY()
	int AttackTargetIndex;

	UPROPERTY(EditDefaultsOnly)
	uint32 MaxNewTargetDistance = 5000;
	
public:
	ASROPlayerController(const FObjectInitializer& ObjectInitializer);
	
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
	bool SetTarget(AActor* NewTarget);

	UFUNCTION(BlueprintCallable, Category=Targeting)
	FORCEINLINE AActor* GetTarget() const { return CurrentTarget; }

	/** Blueprint event to tell attack target updated */
	UFUNCTION(BlueprintImplementableEvent)
	void CurrentTargetUpdated();
	
	/** Blueprint event to tell fight target updated */
	UFUNCTION(BlueprintImplementableEvent)
	void FightTargetUpdated();

	UFUNCTION(BlueprintCallable)
	void CancelAction();

	UFUNCTION(BlueprintCallable)
	void NextAttackTarget();
	
	UFUNCTION(BlueprintCallable)
	void UpdateTargetingUI();

	UFUNCTION(BlueprintCallable)
	void UpdateAttackTargetUI();
	
	UFUNCTION(BlueprintCallable)
	void UpdateFightingTargetUI();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
	UFUNCTION()
	void ControlledPawnTookDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void SetupUIForControlledPawn();
private:
	// HELPER FUNCTIONS
	bool CheckNextAttackTarget(TArray<AActor*> Targets, const int Index);
	// END HELPER FUNCTIONS
};


