// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Character/SROBaseCharacter.h"
#include "Components/Image.h"
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
	USROBaseCharacter* BaseCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UImage* Highlight;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
};
