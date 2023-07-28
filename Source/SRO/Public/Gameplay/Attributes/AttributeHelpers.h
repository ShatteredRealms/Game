// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#define GAMEPLAYATTRIBUTE_VALUE_SETTER_WITHMIN(PropertyName, MinValue) \
	FORCEINLINE void Set##PropertyName(float NewVal) \
	{ \
		NewVal = FMath::Max(NewVal, ##MinValue##); \
		UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent(); \
		if (ensure(AbilityComp)) \
		{ \
			AbilityComp->SetNumericAttributeBase(Get##PropertyName##Attribute(), NewVal); \
		}; \
	}

