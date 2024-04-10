// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SROServerTarget : TargetRules
{
	public SROServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		CppStandard = CppStandardVersion.Latest;
		BuildEnvironment = TargetBuildEnvironment.Unique;
		bUseLoggingInShipping = true;
		ExtraModuleNames.Add("SRO");
	}
}
