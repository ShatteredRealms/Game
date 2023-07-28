// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DraggableResizableBaseWindow.h"
#include "Blueprint/UserWidget.h"
#include "Chat/ChatTabWidget.h"
#include "Combat/VerticalProgressWidget.h"
#include "Components/CanvasPanel.h"
#include "Save/ChatPanelData.h"
#include "SRO/SROGameInstance.h"
#include "Targeting/AttackTargetsWidget.h"

#include "SROBaseUI.generated.h"

class USROSaveGame; 
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

private:
	void Setup_Chat(TArray<FChatPanelData> Data);
	void Setup_CombatBars(USROSaveGame* SaveGame);
	void Setup_Targeting(USROSaveGame* SaveGame);

	USROGameInstance* GameInstance;
	ASROPlayerController* PlayerController;
	
public:
	USROBaseUI(const FObjectInitializer& ObjectInitializer);

	/** The main canvas panel that contains all UI elements. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UCanvasPanel* MainPanel;

	// START CHAT
	/** Array of all the chat panels. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UDraggableResizableBaseWindow*> ChatPanels;

	/** The most recently focused chat panel */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChatTabWidget* PrevFocusedChatTab;
	// END CHAT

	// START TARGETING
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UAttackTargetsWidget* AttackTargetsWidget;
	// END TARGETING

	// START XP, MP, XP Bars
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UVerticalProgressWidget* HealthBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UVerticalProgressWidget* ManaBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UVerticalProgressWidget* ExperienceBar;
	// END XP, MP, XP Bars

	// START WIDGET CLASSES
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDraggableResizableBaseWindow> ChatWindowClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UChatTabWidget> ChatTabWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAttackTargetsWidget> AttackTargetsWidgetClass;
	// END WIDGET CLASSES
public:
	/**
	 * Clears the canvas and setups up the main panel from the save.
	 * @returns true if no internal errors occured. Elements could fail to render if the save file is corrupt but
	 * the function will still return true.
	 */
	UFUNCTION(BlueprintCallable)
	bool SetupFromSave();

private:
	UFUNCTION()
	void OnChatTabSelected(UChatTabWidget* SelectedChatTab);
};
