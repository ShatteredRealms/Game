// Copyright Epic Games, Inc. All Rights Reserved.

#include "Animation/SROAnimInstance.h"

#include "AbilitySystemGlobals.h"
#include "Gameplay/Character/SROCharacter.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SROAnimInstance)


USROAnimInstance::USROAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#if WITH_EDITOR
EDataValidationResult USROAnimInstance::IsDataValid(TArray<FText>& ValidationErrors)
{
	Super::IsDataValid(ValidationErrors);

	GameplayTagPropertyMap.IsDataValid(this, ValidationErrors);

	return ((ValidationErrors.Num() > 0) ? EDataValidationResult::Invalid : EDataValidationResult::Valid);
}
#endif // WITH_EDITOR

void USROAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (AActor* OwningActor = GetOwningActor())
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor))
		{
			GameplayTagPropertyMap.Initialize(this, ASC);
		}
	}
}
