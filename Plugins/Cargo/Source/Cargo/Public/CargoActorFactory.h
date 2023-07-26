// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/UniquePtr.h"
#include "CargoImporterUtilities.h"

class FCargoActorFactoryImpl;

class FCargoActorFactory
{
public:

	FCargoActorFactory();
	~FCargoActorFactory();

	UBlueprint* CreateBlueprintActor(TArray<CargoImporterUtilities::FMeshElement> CreatedMeshes, const std::string& AssetName, UObject* ParentPackage, EObjectFlags Flags, bool bApplyPostEditChange);

private:
	TUniquePtr<FCargoActorFactoryImpl> FactoryImpl;

};