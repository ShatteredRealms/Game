// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DraggableResizableWidget.generated.h"

UENUM(BlueprintType)
enum ESide
{
	TOP = 0,
	RIGHT = 1,
	BOTTOM = 2,
	LEFT = 3,
	TOP_LEFT_CORNER = 4,
	TOP_RIGHT_CORNER = 5,
	BOTTOM_RIGHT_CORNER = 6,
	BOTTOM_LEFT_CORNER = 7
};

/**
 * 
 */
UCLASS()
class SRO_API UDraggableResizableWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	// Widget non-configurable properties
	
	// Thickness of the header
	int HeaderThickness = 25;	
	
private:
	// Internal calculated variables

	/** The vector relative to the original click location. */
	FVector2D OriginalRelativeClickPosition;
	
	FVector2D OriginalClickPosition;
	
	FVector2D OriginalWidgetPosition;
	
	FVector2D OriginalWidgetSize;

	FVector2D ClampedWidgetPosition;

	/** Whether the given edge was clicked */
	bool TopClicked, RightClicked, BottomClicked, LeftClicked;

	/** Whether it's a resizing action */
	bool bResizing;

	/** Whether it's a dragging action */
	bool bDragging;
	
public:
	// Widget configurable properties
	
	/** Whether the widget can be resized */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bResizable = true;
	
	/** Whether the widget can be moved */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDraggable = true;
	
	/** Whether the widget can locked in position and size */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLockable = true;

	/** Whether the widget can closed/deleted */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCloseable = true;

public:
	// Widget configurable variables
	
	/** Whether the widget is locked in position and size. Requires bLockable to be true for this to have an effect. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLocked;

	/** The name of the widget */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = FText::FromString("New Panel");

	/** Thickness from the edge that can still be considered a click on the edge */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double DragThickness = 5;


public:
	// Widget event listeners
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	UFUNCTION(BlueprintCallable)
	virtual FVector2D GetMinSize();

	UFUNCTION(BlueprintCallable)
	virtual FVector2D GetMaxSize();
};
