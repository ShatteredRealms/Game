// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SRO : ModuleRules
{
	public SRO(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

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
			"AIModule",
			"SlateCore",
			"Slate",
			"Networking",
			"Sockets",
			"OpenSSL",
		});
		
		PublicIncludePaths.Add("$(ProjectDir)/Source/ThirdParty");
	}
}
