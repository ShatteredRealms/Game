// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Gameplay/Character/SROCharacterDetails.h"
#include "SROCharacterListEntry.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API USROCharacterListEntry : public UUserWidget, public IUserObjectListEntry 
{
	GENERATED_BODY()

public:
	USROCharacterListEntry(const class FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USROCharacterDetails* CharacterDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UImage* Highlight;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
};
