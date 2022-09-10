// Copyright 2022 Shattered Realms Online

#pragma once

#include "CoreMinimal.h"
#include "SROCharacterSelectorWidget.h"
#include "SROCreateCharacterWidget.h"
#include "GameFramework/HUD.h"
#include "SROLoginHUD.generated.h"

class USROLoginWidget;

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

	UFUNCTION()
	void LoginCompleted() const;

	UFUNCTION()
	void LogoutCompleted() const;

	UFUNCTION()
	void CreateCharacter() const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> LoginWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USROLoginWidget* LoginWidget;	

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> CharacterSelectorWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USROCharacterSelectorWidget* CharacterSelectorWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<USROCreateCharacterWidget> CreateCharacterWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USROCreateCharacterWidget* CreateCharacterWidget;	

};
