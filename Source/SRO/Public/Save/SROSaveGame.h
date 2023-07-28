// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ChatPanelData.h"
#include "GameFramework/SaveGame.h"
#include "SRO/SROPlayerController.h"
#include "SROSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API USROSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chat)
	TArray<FChatPanelData> AllChatPanelData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Combat)
	FVector2D HealthBarPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Combat)
	FVector2D ManaBarPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Combat)
	FVector2D ExperienceBarPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Combat)
	FVector2D AttackTargetsPosition;

	UFUNCTION()
	static USROSaveGame* CreateDefault();

private:
	void CreateDefault_CombatBarPositions();
	void CreateDefault_Chat();
	void CreateDefault_TargetingPosition();
};
