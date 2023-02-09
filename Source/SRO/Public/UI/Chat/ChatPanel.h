// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ChatBoxWidget.h"
#include "ChatTabWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "SRO/SROPlayerController.h"
#include "UI/DraggableResizableWidget.h"
#include "ChatPanel.generated.h"



/**
 * 
 */
UCLASS()
class SRO_API UChatPanel : public UDraggableResizableWidget 
{
	GENERATED_BODY()

	UChatPanel(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	
private:
	/** The player controller that owns this widget */
	ASROPlayerController* PC;

	FChatTabSelectedDelegate OnChatTabSelected;

public:
	// Derived classes
	/** The tab and ChatBox relationship pair */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UChatTabWidget*, UChatBoxWidget*> ChatTabs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChatTabWidget* CurrentTab;
	
	/** Chat Tab Widget BP Class that creates the UI */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UChatTabWidget> ChatTabWidgetClass;

	/** Chat Box Widget BP Class that creates the UI */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UChatBoxWidget> ChatBoxWidgetClass;

public:
	// Widget members
	/** Stores all the chat tabs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* ChannelTabsHorizontalBox;

	/** Stores the currently selected chatbox */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* MessagesScrollBox;

	/** User chat input */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* ChatTextBox;

	/** The background image of the panel */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* BackgroundImage;

public:
	// Panel management functions
	/** Adds a new tab to the chat panel*/
	UFUNCTION(BlueprintCallable)
	UChatTabWidget* CreateTab(const FText& TabName, const TSet<int64> ChannelIds);

	/** Focuses the given tab and shows the paired chatbox */
	UFUNCTION(BlueprintCallable)
	void FocusTab(UChatTabWidget* Tab);

	UFUNCTION(BlueprintCallable)
	UChatBoxWidget* GetCurrentChatBox();

private:
	// Private listeners
	UFUNCTION()
	void OnChatMessageSubmitted(const FText& Text, ETextCommit::Type CommitMethod);
};
