// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/UniquePtr.h"
#include "UObject/ObjectMacros.h"

class Material;
class UMaterialInstanceConstant;
class FCargoMaterialFactoryImpl;

class FCargoMaterialFactory
{
public:
	FCargoMaterialFactory();
	~FCargoMaterialFactory();

	const TArray<UMaterialInstanceConstant*>& CreateMaterials(std::map<std::string, Kb3d::Material*> Materials, UObject* ParentPackage, EObjectFlags Flags);

	const TArray<UMaterialInstanceConstant*>& GetMaterials() const;

	void CleanUp();

private:
	TUniquePtr<FCargoMaterialFactoryImpl> FactoryImpl;
};