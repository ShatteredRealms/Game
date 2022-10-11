// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SRO : ModuleRules
{
	public SRO(ReadOnlyTargetRules Target) : base(Target)
	{
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
		});
	}
}
