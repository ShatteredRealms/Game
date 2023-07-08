// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TabWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "UI/DraggableResizableWidget.h"
#include "DraggableResizableBaseWindow.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API UDraggableResizableBaseWindow : public UDraggableResizableWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UTabWidget* ActiveTab;
	
	FTabSelectedDelegate OnTabSelected;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* OuterPanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CloseButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UNamedSlot* ContentSlot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* WindowBackgroundImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* WindowBorder;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* Tabs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UTabWidget*, UUserWidget*> TabMapping;

	/** Tab Widget BP Class that creates the UI */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UTabWidget> TabWidgetClass;

public:
	UTabWidget* GetActiveTab() const { return ActiveTab; }
	
public:
	virtual void NativeConstruct() override;
	
	UDraggableResizableBaseWindow();
	
	// Panel management functions
	/** Adds a new tab to the chat panel*/
	UFUNCTION(BlueprintCallable)
	UTabWidget* CreateTab(const FText& TabName, UUserWidget* Content);

	UFUNCTION(BlueprintCallable)
	void AppendTab(UTabWidget* Tab, UUserWidget* Content);

	/** Focuses the given tab and shows the paired chatbox */
	UFUNCTION(BlueprintCallable)
	void FocusTab(UTabWidget* Tab);

	UFUNCTION(BlueprintCallable)
	void SetCloseable(bool IsCloseable);
};
