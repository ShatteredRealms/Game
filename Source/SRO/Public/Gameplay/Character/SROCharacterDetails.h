#pragma once

#include "CoreMinimal.h"
#include "SSroCharacter/CharacterMessage.h"
#include "SROCharacterDetails.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SRO_API USROCharacterDetails : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGrpcSroCharacterCharacterDetails GRPCData;
};