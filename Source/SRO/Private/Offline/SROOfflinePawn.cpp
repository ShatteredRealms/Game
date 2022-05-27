// Copyright 2022 Shattered Realms Online


#include "Offline/SROOfflinePawn.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Login/SROLoginWidget.h"

// Sets default values
ASROOfflinePawn::ASROOfflinePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create a follow camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

