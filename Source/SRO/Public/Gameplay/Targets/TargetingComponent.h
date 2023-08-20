// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Targeting/TargetDetailsWidget.h"
#include "TargetingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SRO_API UTargetingComponent : public UWidgetComponent 
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTargetingComponent(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	
	/** Set whether targeted or not. Nothing happens if does not change. */
	UFUNCTION(BlueprintCallable, Category="Targeting")
	void SetTargeted(bool bIsTargeted);

	/** Whether is targeted. */
	UFUNCTION(BlueprintCallable, Category="Targeting")
	bool IsTargeted();
	
	/** Set whether targeted or not. Nothing happens if does not change. */
	UFUNCTION(BlueprintCallable, Category="Targeting")
	void SetAttacked(bool bNewAttacked);

	/** Whether is targeted. */
	UFUNCTION(BlueprintCallable, Category="Targeting")
	bool IsAttacked();

	/** Setter for DisplayName. */
	UFUNCTION(BlueprintCallable, Category="Targeting")
	void SetDisplayName(FString NewName);

	UFUNCTION(BlueprintCallable, Category=Targeting)
	UTargetDetailsWidget* GetDetailsUserWidget();

	UFUNCTION(BlueprintCallable)
	void Setup(AActor* Actor);
};
