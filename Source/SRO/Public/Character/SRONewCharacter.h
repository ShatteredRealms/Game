// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRONewCharacter.generated.h"

UCLASS()
class SRO_API ASRONewCharacter : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Realm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Gender;
	
public:	
	// Sets default values for this actor's properties
	ASRONewCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Whether the character has a gender. Defaults to true.
	bool HasGender();
};
