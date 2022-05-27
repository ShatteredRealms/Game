// Copyright 2022 Shattered Realms Online

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UI/Login/SROLoginWidget.h"
#include "SROOfflinePawn.generated.h"

UCLASS()
class SRO_API ASROOfflinePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASROOfflinePawn();

	/** The camera the player sees from */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
};
