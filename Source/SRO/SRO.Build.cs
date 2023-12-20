// Copyright Epic Games, Inc. All Rights Reserved.

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
		
		PublicIncludePaths.AddRange(new []
		{
			"SRO"
		});

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
			"GameplayTags",
			"GameplayTasks",
			"GameplayAbilities",
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
			"Niagara",
		});
		
		PrivateDependencyModuleNames.AddRange(new []
		{
			"GameplayMessageRuntime",
			"NetCore",
		});

		AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");
		AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");
	}
}