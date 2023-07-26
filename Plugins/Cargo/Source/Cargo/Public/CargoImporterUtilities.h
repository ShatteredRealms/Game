// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IImageWrapper.h"
#include "CargoLibrary/Public/Assembly.h"
#include "CargoLibrary/Public/Instance.h"
#include "CargoLibrary/Public/Material.h"

namespace CargoImporterUtilities
{
	void ImportAssets(std::vector<Kb3d::Instance*> Components, std::map<std::string, Kb3d::Material*> Materials, const std::string& AssetName);

	void AddActorToLevel(UBlueprint* InBlueprint);

	void GetAssembly(Kb3d::Assembly& Assembly);
	void Logger(std::string msg);

	void LoadTexture2D_FromBuffer(const TArray<uint8>& RawFileData, EImageFormat ImageFormat, bool& IsValid, int32& Width, int32& Height, TArray<uint8>& ImageData);

	void LoadTexture2D_FromFile(const FString& FullFilePath, bool& IsValid, int32& Width, int32& Height, TArray<uint8>& ImageData);

	void GetDimensions_FromFile(const FString& FullFilePath, bool& IsValid, int32& Width, int32& Height);

	void SaveAsset(UObject* Asset, const FString& PackageName, UPackage* AssetPackage, EObjectFlags Flags);

	void Async_SaveAsset(UObject* Asset, const FString& PackageName, UPackage* AssetPackage, EObjectFlags Flags);

	EImageFormat GetImageFormat_FromFile(const FString& FullFilePath);

	class FMeshElement
	{
	public:
		FMeshElement(UStaticMesh* StaticMesh, FVector MeshOffset, FString PackageName, UPackage* AssetPackage, EObjectFlags Flags, bool bIsDirty);

		UStaticMesh* StaticMesh;
		FVector MeshOffset;
		FString PackageName;
		UPackage* AssetPackage;
		EObjectFlags Flags;
		bool bIsDirty = true;
	};
}