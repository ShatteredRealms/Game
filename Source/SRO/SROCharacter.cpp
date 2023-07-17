// Copyright Epic Games, Inc. All Rights Reserved.

#include "SROCharacter.h"

#include "SRO.h"
#include "SROPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "UI/SROHud.h"

//////////////////////////////////////////////////////////////////////////
// ASROCharacter

ASROCharacter::ASROCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 1.0f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	MaximumCameraDistance = 800.f;
	MinimumCameraDistance = 150.f;
	BaseCameraZoomRate = 45.f;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	NameText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NameText"));
	NameText->SetupAttachment(RootComponent);
	NameText->SetText(FText::FromString(""));
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	MaxHealth = 100;
	CurrentHealth = MaxHealth;
}

void ASROCharacter::BeginPlay()
{
	Super::BeginPlay();
	ConnectionDateTime = FDateTime::Now();
}

void ASROCharacter::BeginDestroy()
{
	Super::BeginDestroy();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASROCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ASROCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ASROCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &ASROCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ASROCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ASROCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ASROCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ASROCharacter::TouchStopped);

	PlayerInputComponent->BindAction("Adjust Camera", IE_Pressed, this, &ASROCharacter::OnMousePressed);
	PlayerInputComponent->BindAction("Adjust Camera", IE_Released, this, &ASROCharacter::OnMouseReleased);
	
	PlayerInputComponent->BindAction("ZoomCamera", IE_Pressed, this, &ASROCharacter::ZoomCameraAtRate);
	
	PlayerInputComponent->BindAction("Next Fighting Target", IE_Pressed, this, &ASROCharacter::NextFightingTarget);
}

void ASROCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ASROCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ASROCharacter::OnMousePressed()
{
	IsMouseDown = true;
}

void ASROCharacter::OnMouseReleased()
{
	IsMouseDown = false;
}

void ASROCharacter::ZoomCameraAtRate(FKey Key)
{
	float NewDistance = CameraBoom->TargetArmLength;
	if (Key == EKeys::MouseScrollDown)
	{
		NewDistance += BaseCameraZoomRate;
	}
	else
	{
		NewDistance -= BaseCameraZoomRate;
	}
	

	CameraBoom->TargetArmLength = FMath::Clamp(
		NewDistance,
		MinimumCameraDistance,
		MaximumCameraDistance);
}

void ASROCharacter::NextFightingTarget()
{
	
}

void ASROCharacter::AddControllerYawInput(float Value)
{
	Super::AddControllerYawInput(Value);

	if (!IsMouseDown)
	{
		MoveRight(0);
	}
}

void ASROCharacter::TurnAtRate(float Rate)
{
	if (IsMouseDown)
	{
		MoveRight(Rate);
		return;
	}
	
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ASROCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

FUInt64 ASROCharacter::GetPlayTimespan() const
{
	const auto span = FDateTime::Now().ToUnixTimestamp() - ConnectionDateTime.ToUnixTimestamp();
	if (span < 0)
	{
		return 0;
	}

	return FUInt64{static_cast<unsigned long long>(span)};
}

void ASROCharacter::SetBaseCharacter(FGrpcSroCharacterCharacterDetails NewCharacterDetails)
{
	
	if (GetLocalRole() == ROLE_Authority)
	{
		CharacterDetails = NewCharacterDetails;
		OnCharacterDetailsUpdated();
	}
}


void ASROCharacter::OnRep_CharacterDetails()
{
	OnCharacterDetailsUpdated();
}

void ASROCharacter::OnCharacterDetailsUpdated()
{
	NameText->SetText(FText::FromString(CharacterDetails.Name));
	if (CharacterDetails.Name != "")
	{
		NameText->SetVisibility(true);
	}
}

FGrpcSroCharacterCharacterDetails& ASROCharacter::GetCharacterDetails()
{
	return CharacterDetails;
}

void ASROCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASROCharacter, CharacterDetails);
	DOREPLIFETIME(ASROCharacter, FightingTarget);
}

void ASROCharacter::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);
	ASROPlayerController* PC = Cast<ASROPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->SetTarget(this);
	}
}

void ASROCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASROCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

