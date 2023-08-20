// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gameplay/Targets/Targetable.h"
#include "BaseCharacter.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SRO_API ABaseCharacter : public ACharacter, public ITargetable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Targeting)
	UTargetingComponent* TargetingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Targeting)
	FString DisplayName;
	
public:
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable)
	virtual UTargetingComponent* GetTargetingComponent() override;

	UFUNCTION(BlueprintCallable)
	void SetDisplayName(FString NewDisplayName);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetDisplayName() const { return DisplayName; }
};
