// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class SRO_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes)
	TSubclassOf<AAIController> DefaultAIClass;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OnTargetedChanged_Implementation() override;
	virtual void OnIsAttackedUpdated_Implementation() override;
	virtual void OnCurrentHealthUpdated_Implementation() override;
	virtual void OnMaxHealthUpdated_Implementation() override;
};
