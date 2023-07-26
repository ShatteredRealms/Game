// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/UniquePtr.h"
#include "UObject/ObjectMacros.h"

class Instance;
class FMeshElement;
class FCargoStaticMeshFactoryImpl;

struct FMeshDescription;

class FCargoStaticMeshFactory
{
public:

	FCargoStaticMeshFactory();
	~FCargoStaticMeshFactory();

	const TArray<CargoImporterUtilities::FMeshElement>& CreateMeshes(std::vector<Kb3d::Instance*> Components, UObject* ParentPackage, EObjectFlags Flags, bool bApplyPostEditChange);

	void FillMeshDescription(Kb3d::Instance* Instance, FMeshDescription* MeshDescription);

	const TArray<CargoImporterUtilities::FMeshElement>& GetMeshes() const;

	void CleanUp();

private:
	TUniquePtr<FCargoStaticMeshFactoryImpl> FactoryImpl;

};

