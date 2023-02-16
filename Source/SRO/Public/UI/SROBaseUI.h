// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Chat/ChatPanel.h"
#include "Components/CanvasPanel.h"
#include "SROBaseUI.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API USROBaseUI : public UUserWidget
{
	GENERATED_BODY()

	/**
	 * Calls the setup from save function
	 */
	virtual void NativeConstruct() override;

	/** BP Chat panel class that implements the UI design */
	TSubclassOf<UChatPanel> ChatPanelClass;
	
public:
	USROBaseUI(const FObjectInitializer& ObjectInitializer);

	/** The main canvas panel that contains all UI elements. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UCanvasPanel* MainPanel;

	/** Array of all the chat panels. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UChatPanel*> ChatPanels;

public:
	/**
	 * Clears the canvas and setups up the main panel from the save.
	 * @returns true if no internal errors occured. Elements could fail to render if the save file is corrupt but
	 * the function will still return true.
	 */
	UFUNCTION(BlueprintCallable)
	bool SetupFromSave();
};
