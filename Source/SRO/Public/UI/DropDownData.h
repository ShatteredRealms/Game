// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DropDownData.generated.h"

class UDropDownData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDropDownSelected, UDropDownData*, SelectedData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDropDownClicked, UDropDownData*, ClickedData);

/**
 * 
 */
UCLASS(Blueprintable)
class SRO_API UDropDownData : public UObject
{
	GENERATED_BODY()	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* DataObject;
	
	// What to display in the dropdown
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	// Whether this should open another drop down
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDropDown;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDropDownSelected OnSelected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDropDownClicked OnClicked;

	UPROPERTY(BlueprintReadOnly)
	bool bHovered;
};
