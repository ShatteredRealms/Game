// Copyright Shattered Realms Online All Rights Reserved


#include "Character/SRONewCharacter.h"

// Sets default values
ASRONewCharacter::ASRONewCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASRONewCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASRONewCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASRONewCharacter::HasGender()
{
	return true;
}

