// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class CargoLibrary : ModuleRules
{
	public CargoLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
        PrecompileForTargets = PrecompileTargetsType.Any;
        bUsePrecompiled = true;

        if (Target.Platform == UnrealTargetPlatform.Win64)
		{
            // Add the import library
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
            PublicSystemLibraryPaths.Add(Path.Combine(ModuleDirectory, "x64", "Release"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "KBUSD.lib"));
        }
	}
}
