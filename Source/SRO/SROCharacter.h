// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/SROBaseCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/PassiveTarget.h"
#include "SROCharacter.generated.h"

UCLASS(config=Game)
class ASROCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Name above the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* NameText;
	
	/** Font used when character is selected */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
	UFont* SelectedFont;

	/** Font used when character is not selected */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
	UFont* UnselectedFont;

	/** Date time connected to the server */
	FDateTime ConnectionDateTime;

	/** Base character details */
	UPROPERTY(ReplicatedUsing = OnRep_CharacterDetails)
	FGrpcSroCharacterCharacterDetails CharacterDetails;

	UFUNCTION()
	void OnRep_CharacterDetails();
	
	void OnCharacterDetailsUpdated();
	
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

	/** Whether the mouse is currently down */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	bool IsMouseDown;
	
public:
	ASROCharacter();

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	
	/** Get the time in seconds the player has been connected */
	UFUNCTION(BlueprintCallable)
	FUInt64 GetPlayTimespan() const;

	/** Set the base character details */
	UFUNCTION(BlueprintCallable)
	void SetBaseCharacter(FGrpcSroCharacterCharacterDetails NewCharacterDetails);

	/** Get the base character details */
	UFUNCTION(BlueprintCallable)
	FGrpcSroCharacterCharacterDetails& GetCharacterDetails();
	
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const override;

	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

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

	/** Target the next fighting target */
	void NextFightingTarget();
	
	virtual void AddControllerYawInput(float Value) override;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns the character's name. */
	virtual FORCEINLINE FString GetDisplayName() override { return CharacterDetails.Name; };

private:
};



