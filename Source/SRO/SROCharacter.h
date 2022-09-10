// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/SROBaseCharacter.h"
#include "GameFramework/Character.h"
#include "SROCharacter.generated.h"

UCLASS(config=Game)
class ASROCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	ASROCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	/** The minimum distance the camera can get to the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float MinimumCameraDistance;

	/** The maximum distance the camera can get from the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float MaximumCameraDistance;

	/** The rate at which the camera zooms in and out */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseCameraZoomRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	bool IsMouseDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	USROBaseCharacter* BaseCharacter;
protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/** Called when the mouse is pressed down */
	void OnMousePressed();

	/** Called when the mouse is released */
	void OnMouseReleased();

	/**
	 * Called for zooming in/out input.
	 * @param Key Key pressed that initiated the zoom. 
	 */
	void ZoomCameraAtRate(FKey Key);
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

