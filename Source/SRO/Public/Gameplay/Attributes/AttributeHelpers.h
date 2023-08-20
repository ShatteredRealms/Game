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

#define GAMEPLAYATTRIBUTE_HELPERS(ClassName, PropertyName) \
	UFUNCTION() \
	FORCEINLINE void OnRep_##PropertyName(const FGameplayAttributeData& Old##PropertyName##) \
	{ \
		GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, ##PropertyName##, Old##PropertyName##); \
	}; \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
	

#define GAMEPLAYATTRIBUTE_ALLDEFAULT(ClassName, PropertyName, CategoryString) \
	protected: \
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_##PropertyName##, Category=CategoryString) \
	FGameplayAttributeData PropertyName##; \
	public: \
	GAMEPLAYATTRIBUTE_HELPERS(ClassName, PropertyName)

#define GA_SET_IF(PropertyName, MinValue, MaxValue) \
	if (Data.EvaluatedData.Attribute == Get##PropertyName##Attribute()) \
	{ \
		Set##PropertyName##(FMath::Clamp(Get##PropertyName##(), MinValue, MaxValue)); \
	}

#define GA_SET_ELSEIF(PropertyName, MinValue, MaxValue) \
	else if (Data.EvaluatedData.Attribute == Get##PropertyName##Attribute()) \
	{ \
		Set##PropertyName##(FMath::Clamp(Get##PropertyName##(), MinValue, MaxValue)); \
	}
