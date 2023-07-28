// Copyright Shattered Realms Online All Rights Reserved


#include "Gameplay/NPC/NPC.h"

#include "UI/Targeting/TargetDetailsWidget.h"

// Sets default values
ANPC::ANPC() : Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FClassFinder<AAIController> FoundDefaultAIClass(TEXT("/Game/SRO/Core/Gameplay/NPC/AI_NPC"));
	if (FoundDefaultAIClass.Class != NULL)
	{
		DefaultAIClass = FoundDefaultAIClass.Class;
	}
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;
	
	if (UTargetDetailsWidget* TargetDetailsWidget = Cast<UTargetDetailsWidget>(GetDetailsUserWidget()))
	{
		TargetDetailsWidget->Setup(this);
	}
}

void ANPC::OnTargetedChanged_Implementation()
{
	Super::OnTargetedChanged_Implementation();
	if (UTargetDetailsWidget* TargetDetailsWidget = Cast<UTargetDetailsWidget>(GetDetailsUserWidget()))
	{
		TargetDetailsWidget->SetTargeted(bTargeted);
	}
}

void ANPC::OnIsAttackedUpdated_Implementation()
{
	Super::OnIsAttackedUpdated_Implementation();
	if (UTargetDetailsWidget* TargetDetailsWidget = Cast<UTargetDetailsWidget>(GetDetailsUserWidget()))
	{
		TargetDetailsWidget->SetFightingTarget(bAttacked);
	}
}

void ANPC::OnCurrentHealthUpdated_Implementation()
{
	Super::OnCurrentHealthUpdated_Implementation();
	if (UTargetDetailsWidget* TargetDetailsWidget = Cast<UTargetDetailsWidget>(GetDetailsUserWidget()))
	{
		TargetDetailsWidget->UpdateHealthPercentage();
	}
}

void ANPC::OnMaxHealthUpdated_Implementation()
{
	Super::OnMaxHealthUpdated_Implementation();
	if (UTargetDetailsWidget* TargetDetailsWidget = Cast<UTargetDetailsWidget>(GetDetailsUserWidget()))
	{
		TargetDetailsWidget->UpdateHealthBarSize();
		TargetDetailsWidget->UpdateHealthPercentage();
	}
}
