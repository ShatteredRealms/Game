// Copyright 2022 Shattered Realms Online


#include "SROOfflinePawn.h"

// Sets default values
ASROOfflinePawn::ASROOfflinePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASROOfflinePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASROOfflinePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASROOfflinePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

