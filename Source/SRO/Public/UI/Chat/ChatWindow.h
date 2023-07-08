// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UI/DraggableResizableBaseWindow.h"
#include "ChatWindow.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API UChatWindow : public UDraggableResizableBaseWindow
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
};
