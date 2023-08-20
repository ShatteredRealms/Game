// Copyright Shattered Realms Online All Rights Reserved


#include "Gameplay/Character/NPC/NPC.h"

#include "UI/Targeting/TargetDetailsWidget.h"

// Sets default values
ANPC::ANPC(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
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

	if (!HasAuthority())
	{
		GetTargetingComponent()->Setup(this);
	}
}
