// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoveableWidget.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API UMoveableWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	/** The vector relative to the original click location. */
	FVector2D OriginalRelativeClickPosition;
	
	FVector2D OriginalClickPosition;
	
	FVector2D OriginalWidgetPosition;
	
	bool bDragging;

	bool bHovering;
public:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
};
