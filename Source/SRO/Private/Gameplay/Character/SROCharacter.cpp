// Copyright Epic Games, Inc. All Rights Reserved.

#include "Gameplay/Character/SROCharacter.h"

#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SRO/SROPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "UI/SROHud.h"
#include "UI/Targeting/TargetDetailsWidget.h"

//////////////////////////////////////////////////////////////////////////
// ASROCharacter

ASROCharacter::ASROCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
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
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	
	// MaxHealth = 100;
	// CurrentHealth = MaxHealth;
}

void ASROCharacter::BeginPlay()
{
	Super::BeginPlay();
	ConnectionDateTime = FDateTime::Now();
	if (ASROPlayerController* PlayerController = Cast<ASROPlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

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
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASROCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASROCharacter::Look);
		EnhancedInputComponent->BindAction(LookResetAction, ETriggerEvent::Triggered, this, &ASROCharacter::LookReset);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ASROCharacter::Look);

		// Zooming
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ASROCharacter::ZoomCameraAtRate);
		
		// Canceling
		EnhancedInputComponent->BindAction(CancelAction, ETriggerEvent::Triggered, this, &ASROCharacter::Cancel);

		// Attack 
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASROCharacter::Attack);

		// New Attack Target
		EnhancedInputComponent->BindAction(NextAttackTargetAction, ETriggerEvent::Triggered, this, &ASROCharacter::NewAttackTarget);
	}
}

void ASROCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASROCharacter::LookReset(const FInputActionValue& Value)
{
	if (Controller != nullptr && GetMesh())
	{
		FRotator3d NewRotator = Controller->GetControlRotation();
		NewRotator.Yaw = GetMesh()->GetComponentRotation().Yaw - GetMesh()->GetRelativeRotation().Yaw;
		Controller->SetControlRotation(NewRotator);
	}
}

void ASROCharacter::ResetFaceFightingTargetTimer_Implementation()
{
	
}

void ASROCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		// const FRotator Rotation = GetMesh()->GetComponentRotation() - GetMesh()->GetRelativeRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}
void ASROCharacter::ZoomCameraAtRate(const FInputActionValue& Value)
{
	float NewDistance = CameraBoom->TargetArmLength + BaseCameraZoomRate + Value.GetMagnitude();

	CameraBoom->TargetArmLength = FMath::Clamp(
		NewDistance,
		MinimumCameraDistance,
		MaximumCameraDistance);
}

void ASROCharacter::NextFightingTarget(const FInputActionValue& Value)
{
	ASROPlayerController* PC = GetController<ASROPlayerController>();
	if (PC)
	{
		PC->NextAttackTarget();
	}
}

void ASROCharacter::Cancel(const FInputActionValue& Value)
{
	if (FightingTarget)
	{
		StopFighting();
		return;
	}

	ASROPlayerController* PC = GetController<ASROPlayerController>();
	if (PC)
	{
		PC->CancelAction();
	}
}

void ASROCharacter::Attack(const FInputActionValue& Value)
{
	ASROPlayerController* PC = GetController<ASROPlayerController>();
	if (PC)
	{
		PC->StartAttack();
	}
}

void ASROCharacter::NewAttackTarget(const FInputActionValue& Value)
{
	ASROPlayerController* PC = GetController<ASROPlayerController>();
	if (PC)
	{
		PC->NextAttackTarget();
	}
}

void ASROCharacter::StartFighting(AFightingCharacter* Target)
{
	Super::StartFighting(Target);
	if(IsLocallyControlled())
	{
		ASROPlayerController* PC = GetController<ASROPlayerController>();
		if (PC)
		{
			PC->UpdateFightingTargetUI();
		}
	}
}

void ASROCharacter::StopFighting()
{
	Super::StopFighting();
	if(IsLocallyControlled())
	{
		ASROPlayerController* PC = GetController<ASROPlayerController>();
		if (PC)
		{
			PC->UpdateFightingTargetUI();
		}
	}
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
		DisplayName = NewCharacterDetails.Name;
		OnCharacterDetailsUpdated();
	}
}

void ASROCharacter::OnRep_CharacterDetails()
{
	OnCharacterDetailsUpdated();
}

void ASROCharacter::OnCharacterDetailsUpdated_Implementation()
{
	if (IsLocallyControlled())
	{
		DisplayName = CharacterDetails.Name;
		GetTargetingComponent()->Setup(this);
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

