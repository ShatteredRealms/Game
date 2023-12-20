#pragma once

#include "CoreMinimal.h"
#include "SSroCharacter/CharacterMessage.h"
#include "SROCharacterDetails.generated.h"

/**
 * SRO Character Details received from a gRPC call
 */
UCLASS(Blueprintable)
class SRO_API USROCharacterDetails : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGrpcSroCharacterCharacterDetails GRPCData;
};