// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Targetable.h"
#include "GameFramework/Actor.h"
#include "StationaryTarget.generated.h"

UCLASS(Blueprintable)
class SRO_API AStationaryTarget : public AActor, public ITargetable
{
	GENERATED_BODY()
	
protected:
	/** The main skeletal mesh associated with this Character (optional sub-object). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Targeting)
	UTargetingComponent* TargetingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Targeting)
	FString DisplayName;
	
public:	
	// Sets default values for this actor's properties
	AStationaryTarget(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual UTargetingComponent* GetTargetingComponent() override;

	UFUNCTION(BlueprintCallable)
	void SetDisplayName(FString NewDisplayName);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetDisplayName() const { return DisplayName; }
};
