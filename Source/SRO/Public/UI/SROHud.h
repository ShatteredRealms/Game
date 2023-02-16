// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SROBaseUI.h"
#include "GameFramework/HUD.h"
#include "SROHud.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API ASROHud : public AHUD
{
	GENERATED_BODY()

	
protected:
	virtual void BeginPlay() override;

	TSubclassOf<USROBaseUI> BaseUIClass;
	
public:
	ASROHud();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USROBaseUI* BaseUI;
};
