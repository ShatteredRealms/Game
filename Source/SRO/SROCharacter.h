// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Character/SROBaseCharacter.h"
#include "GameFramework/Character.h"
#include "UI/Targeting/TargetDetailsWidget.h"
#include "SROCharacter.generated.h"

UCLASS(config=Game)
class SRO_API ASROCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Turn Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* TurnAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookResetAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ZoomAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CancelAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* NextAttackTargetAction;

	/** Date time connected to the server */
	FDateTime ConnectionDateTime;

	/** Base character details */
	UPROPERTY(ReplicatedUsing = OnRep_CharacterDetails)
	FGrpcSroCharacterCharacterDetails CharacterDetails;

	/** The minimum distance the camera can get to the player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	float MinimumCameraDistance;

	/** The maximum distance the camera can get from the player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	float MaximumCameraDistance;

	/** The rate at which the camera zooms in and out */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	float BaseCameraZoomRate;

	// REPLICATION
	UFUNCTION()
	void OnRep_CharacterDetails();
	// REPLICATION
	
public:
	ASROCharacter(const FObjectInitializer& ObjectInitializer);

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
	
	UFUNCTION(BlueprintNativeEvent)
	void OnCharacterDetailsUpdated();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ResetFaceFightingTargetTimer();
	
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for looking with rotation input */
	void LookReset(const FInputActionValue& Value);

	/**
	 * Called for zooming in/out input.
	 * @param Key Key pressed that initiated the zoom. 
	 */
	void ZoomCameraAtRate(const FInputActionValue& Value);

	/** Target the next fighting target */
	void NextFightingTarget(const FInputActionValue& Value);

	/** Cancel actions */
	void Cancel(const FInputActionValue& Value);

	/** Start attacking */
	void Attack(const FInputActionValue& Value);

	/** Request player controller to find a new attack target */
	void NewAttackTarget(const FInputActionValue& Value);
	
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

	virtual void StartFighting(AFightingTarget* Target) override;

	virtual void StopFighting() override;

	virtual void OnTargetedChanged_Implementation() override;
	virtual void OnCurrentHealthUpdated_Implementation() override;
	virtual void OnMaxHealthUpdated_Implementation() override;
};



