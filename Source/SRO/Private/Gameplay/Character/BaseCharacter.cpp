// Copyright Shattered Realms Online All Rights Reserved


#include "Gameplay/Character/BaseCharacter.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	TargetingComponent = CreateDefaultSubobject<UTargetingComponent>(TEXT("TargetingComponent"));
	TargetingComponent->SetupAttachment(RootComponent);
}

UTargetingComponent* ABaseCharacter::GetTargetingComponent()
{
	return TargetingComponent;
}

void ABaseCharacter::SetDisplayName(FString NewDisplayName)
{
	DisplayName = NewDisplayName;
	TargetingComponent->SetDisplayName(DisplayName);
}
