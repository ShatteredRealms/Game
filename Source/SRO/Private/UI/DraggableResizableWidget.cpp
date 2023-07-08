// Copyright Shattered Realms Online All Rights Reserved


#include "UI/DraggableResizableWidget.h"

#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetMathLibrary.h"

FReply UDraggableResizableWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry,
                                                          const FPointerEvent& InMouseEvent)
{
	GEngine->AddOnScreenDebugMessage(100, 0.1f, FColor::Red, "MouseDown");
	if (!InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return FReply::Unhandled();
	}

	FVector2D PixelPosition;
	USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(),
	                                           InMouseEvent.GetScreenSpacePosition(),
	                                           PixelPosition,
	                                           OriginalClickPosition);


	//@TODO: Test - Can slot be deleted immediately after being used?
	const auto CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	OriginalWidgetPosition = CanvasPanelSlot->GetPosition();
	OriginalWidgetSize = CanvasPanelSlot->GetSize();
	ClampedWidgetPosition = OriginalWidgetPosition + OriginalWidgetSize - MinSize;
	OriginalRelativeClickPosition = OriginalClickPosition - OriginalWidgetPosition;

	if (bResizable)
	{
		TopClicked = UKismetMathLibrary::InRange_FloatFloat(OriginalRelativeClickPosition.Y,
		                                                    0,
		                                                    DragThickness);

		RightClicked = UKismetMathLibrary::InRange_FloatFloat(OriginalRelativeClickPosition.X,
		                                                      OriginalWidgetSize.X - DragThickness,
		                                                      OriginalWidgetSize.X);

		BottomClicked = UKismetMathLibrary::InRange_FloatFloat(OriginalRelativeClickPosition.Y,
		                                                       OriginalWidgetSize.Y - DragThickness,
		                                                       OriginalWidgetSize.Y);

		LeftClicked = UKismetMathLibrary::InRange_FloatFloat(OriginalRelativeClickPosition.X,
		                                                     0,
		                                                     DragThickness);
	}

	if (TopClicked || RightClicked || LeftClicked || BottomClicked)
	{
		bResizing = true;
	}
	else if (bDraggable)
	{
		bDragging = UKismetMathLibrary::InRange_FloatFloat(OriginalRelativeClickPosition.Y,
		                                                   DragThickness,
		                                                   HeaderThickness - DragThickness);
	}


	auto Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return UWidgetBlueprintLibrary::CaptureMouse(Reply, this).NativeReply;
}

FReply UDraggableResizableWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FVector2D CurrentMousePosition;
	FVector2D CurrentPixelPosition;
	const FVector2D MouseAbsoluteDesktopPosition = InMouseEvent.GetScreenSpacePosition();
	USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(),
	                                           MouseAbsoluteDesktopPosition,
	                                           CurrentPixelPosition,
	                                           CurrentMousePosition);

	if (!bDragging && !bResizing)
	{
		FVector2D RelativeHoverPosition = CurrentMousePosition - UWidgetLayoutLibrary::SlotAsCanvasSlot(this)->
			GetPosition();
		const bool TopHovered = UKismetMathLibrary::InRange_FloatFloat(RelativeHoverPosition.Y,
		                                                               0,
		                                                               DragThickness);

		const bool RightHovered = UKismetMathLibrary::InRange_FloatFloat(RelativeHoverPosition.X,
		                                                                 OriginalWidgetSize.X - DragThickness,
		                                                                 OriginalWidgetSize.X);

		const bool BottomHovered = UKismetMathLibrary::InRange_FloatFloat(RelativeHoverPosition.Y,
		                                                                  OriginalWidgetSize.Y - DragThickness,
		                                                                  OriginalWidgetSize.Y);

		const bool LeftHovered = UKismetMathLibrary::InRange_FloatFloat(RelativeHoverPosition.X,
		                                                                0,
		                                                                DragThickness);

		const bool DragHovered = UKismetMathLibrary::InRange_FloatFloat(RelativeHoverPosition.Y,
		                                                   DragThickness,
		                                                   HeaderThickness - DragThickness);

		
		if ((TopHovered && LeftHovered) || (BottomHovered && RightHovered))
		{
			GetOwningPlayer()->CurrentMouseCursor = EMouseCursor::Type::ResizeSouthEast;
		}
		else if ((TopHovered && RightHovered) || (BottomHovered && LeftHovered))
		{
			
			GetOwningPlayer()->CurrentMouseCursor = EMouseCursor::Type::ResizeSouthWest;
		}
		else if (TopHovered || BottomHovered)
		{
			GetOwningPlayer()->CurrentMouseCursor = EMouseCursor::Type::ResizeUpDown;
		}
		else if (LeftHovered || RightHovered)
		{
			GetOwningPlayer()->CurrentMouseCursor = EMouseCursor::Type::ResizeLeftRight;
		}
		else if (DragHovered)
		{
			GetOwningPlayer()->CurrentMouseCursor = EMouseCursor::Type::Hand;
		}
		else
		{
			GetOwningPlayer()->CurrentMouseCursor = EMouseCursor::Type::Default;
		}

		return FEventReply{}.NativeReply;
	}

	const FVector2D MouseDelta = OriginalClickPosition - CurrentMousePosition;

	auto CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	const FVector2D CurrentMousePositionOffset = CurrentMousePosition - OriginalRelativeClickPosition;
	const FVector2D CurrentRelativeClickPosition = CurrentMousePosition - CanvasPanelSlot->GetPosition();


	// GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::White,
	//                                  FString::Printf(
	// 	                                 TEXT("OriginalRelativeClickPosition: %f.2, %f.2"),
	// 	                                 OriginalRelativeClickPosition.X, OriginalRelativeClickPosition.Y), true,
	//                                  FVector2D{2, 2});
	// GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::White,
	//                                  FString::Printf(
	// 	                                 TEXT("OriginalClickPosition: %f.2, %f.2"), OriginalClickPosition.X,
	// 	                                 OriginalClickPosition.Y), true, FVector2D{2, 2});
	// GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::White,
	//                                  FString::Printf(
	// 	                                 TEXT("OriginalWidgetPosition: %f.2, %f.2"), OriginalWidgetPosition.X,
	// 	                                 OriginalWidgetPosition.Y), true, FVector2D{2, 2});
	// GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::White,
	//                                  FString::Printf(
	// 	                                 TEXT("OriginalWidgetSize: %f.2, %f.2"), OriginalWidgetSize.X,
	// 	                                 OriginalWidgetSize.Y), true, FVector2D{2, 2});
	// GEngine->AddOnScreenDebugMessage(5, 5.f, FColor::White,
	//                                  FString::Printf(
	// 	                                 TEXT("ClampedWidgetPosition: %f.2, %f.2"), ClampedWidgetPosition.X,
	// 	                                 ClampedWidgetPosition.Y), true, FVector2D{2, 2});
	// GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::White,
	//                                  FString::Printf(TEXT("MouseDelta: %f.2, %f.2"), MouseDelta.X, MouseDelta.Y), true,
	//                                  FVector2D{2, 2});
	// GEngine->AddOnScreenDebugMessage(6, 5.f, FColor::White,
	//                                  FString::Printf(
	// 	                                 TEXT("CurrentMousePosition: %f.2, %f.2"), CurrentMousePosition.X,
	// 	                                 CurrentMousePosition.Y), true, FVector2D{2, 2});
	// GEngine->AddOnScreenDebugMessage(8, 5.f, FColor::White,
	//                                  FString::Printf(
	// 	                                 TEXT("ScreenSpacePos: %f.2, %f.2"), MouseAbsoluteDesktopPosition.X,
	// 	                                 MouseAbsoluteDesktopPosition.Y), true, FVector2D{2, 2});
	// GEngine->AddOnScreenDebugMessage(9, 5.f, FColor::White,
	//                                  FString::Printf(
	// 	                                 TEXT("CurrentMousePositionOffset: %f.2, %f.2"), CurrentMousePositionOffset.X,
	// 	                                 CurrentMousePositionOffset.Y), true, FVector2D{2, 2});


	// return FReply::Handled();

	if (bDragging)
	{
		GetOwningPlayer()->CurrentMouseCursor = EMouseCursor::Type::GrabHand;
		CanvasPanelSlot->SetPosition(CurrentMousePosition - OriginalRelativeClickPosition);
	}
	else if (bResizing)
	{
		FVector2D NewSize = CanvasPanelSlot->GetSize();
		FVector2D NewPos = CanvasPanelSlot->GetPosition();

		if (RightClicked)
		{
			NewSize.X = FMath::Clamp(CurrentRelativeClickPosition.X, MinSize.X, MaxSize.X);
		}

		if (BottomClicked)
		{
			NewSize.Y = FMath::Clamp(CurrentRelativeClickPosition.Y, MinSize.Y, MaxSize.Y);
		}

		if (LeftClicked)
		{
			NewSize.X = FMath::Clamp(OriginalWidgetSize.X + MouseDelta.X, MinSize.X, MaxSize.X);
			NewPos.X = FMath::Min(ClampedWidgetPosition.X, CurrentMousePositionOffset.X);
		}

		if (TopClicked)
		{
			NewSize.Y = FMath::Clamp(OriginalWidgetSize.Y + MouseDelta.Y, MinSize.Y, MaxSize.Y);
			NewPos.Y = FMath::Min(ClampedWidgetPosition.Y, CurrentMousePositionOffset.Y);
		}

		CanvasPanelSlot->SetSize(NewSize);
		if (TopClicked || LeftClicked)
		{
			CanvasPanelSlot->SetPosition(NewPos);
		}
	}

	return FEventReply{}.NativeReply;
}


FReply UDraggableResizableWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry,
                                                        const FPointerEvent& InMouseEvent)
{
	bResizing = false;
	bDragging = false;
	GetOwningPlayer()->CurrentMouseCursor = EMouseCursor::Type::Default;
	auto Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return UWidgetBlueprintLibrary::ReleaseMouseCapture(Reply).NativeReply;
}

void UDraggableResizableWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (!bResizing || !bDragging)
	{
		GetOwningPlayer()->CurrentMouseCursor = EMouseCursor::Type::Default;
	}
}
