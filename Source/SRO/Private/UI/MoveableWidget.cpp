// Copyright Shattered Realms Online All Rights Reserved


#include "UI/MoveableWidget.h"

#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetMathLibrary.h"
#include "SRO/SRO.h"

FReply UMoveableWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}
	
	const auto CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	if (!CanvasPanelSlot)
	{
		return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}

	FVector2D PixelPosition;
	USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(),
	                                           InMouseEvent.GetScreenSpacePosition(),
	                                           PixelPosition,
	                                           OriginalClickPosition);
	
	OriginalWidgetPosition = CanvasPanelSlot->GetPosition();
	OriginalRelativeClickPosition = OriginalClickPosition - OriginalWidgetPosition;
	bDragging = true;
	
	auto Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return UWidgetBlueprintLibrary::CaptureMouse(Reply, this).NativeReply;
}

FReply UMoveableWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	if (!CanvasPanelSlot)
	{
		return Super::NativeOnMouseMove(InGeometry, InMouseEvent);
	}
	
	FVector2D CurrentMousePosition;
	FVector2D CurrentPixelPosition;
	const FVector2D MouseAbsoluteDesktopPosition = InMouseEvent.GetScreenSpacePosition();
	USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(),
	                                           MouseAbsoluteDesktopPosition,
	                                           CurrentPixelPosition,
	                                           CurrentMousePosition);
	
	const FVector2D MouseDelta = OriginalClickPosition - CurrentMousePosition;
	
	if (bDragging)
	{
		GetOwningPlayer()->CurrentMouseCursor = EMouseCursor::Type::GrabHand;
		CanvasPanelSlot->SetPosition(CurrentMousePosition - OriginalRelativeClickPosition);
		return FReply::Handled();
	}
	
	GetOwningPlayer()->CurrentMouseCursor = EMouseCursor::Type::Hand;
	bHovering = true;
	
	return Super::NativeOnMouseMove(InGeometry, InMouseEvent);
}

FReply UMoveableWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	bDragging = false;
	auto Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return UWidgetBlueprintLibrary::ReleaseMouseCapture(Reply).NativeReply;
}

void UMoveableWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (!bDragging)
	{
		GetOwningPlayer()->CurrentMouseCursor = EMouseCursor::Type::Default;
	}

	bHovering = true;
	
	Super::NativeOnMouseLeave(InMouseEvent);
}
