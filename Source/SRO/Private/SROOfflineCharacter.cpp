// Copyright 2022 Shattered Realms Online


#include "SROOfflineCharacter.h"

// Sets default values
ASROOfflineCharacter::ASROOfflineCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASROOfflineCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASROOfflineCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASROOfflineCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

