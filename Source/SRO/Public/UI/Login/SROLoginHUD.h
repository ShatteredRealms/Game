// Copyright 2022 Shattered Realms Online

#pragma once

#include "CoreMinimal.h"
#include "SROLoginWidget.h"
#include "GameFramework/HUD.h"
#include "SROLoginHUD.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API ASROLoginHUD : public AHUD
{
	GENERATED_BODY()

public:
	ASROLoginHUD();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void Login() const;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> LoginWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USROLoginWidget* LoginWidget;	
};
