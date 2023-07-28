// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.Collections.Generic;
using System.IO;
using UnrealBuildTool;

public class SRO : ModuleRules
{
	public SRO(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "OculusEditor"  });
		CppStandard = CppStandardVersion.Cpp17;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnableExceptions = true;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"HTTP",
			"Json",
			"JsonUtilities",
			"ReplicationGraph",
			"Agones",
			"UMG",
			"Messaging",
			"MessagingCommon",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"AIModule",
			"SlateCore",
			"Slate",
			"Networking",
			"Sockets",
			"OpenSSL",
			"JWTPlugin",
			"ChunkDownloader",
			"Serialization",
			"TurboLinkGrpc",
			"EnhancedInput",
			"ALSReplicated",
			"NavigationSystem",
		});

		AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");
		AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");
	}
}