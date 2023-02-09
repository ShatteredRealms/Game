// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.Collections.Generic;
using System.IO;
using UnrealBuildTool;

public class SRO : ModuleRules
{
	private static SROPlatform SROPlatformInstance;

	public SRO(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnableExceptions = true;
		SROPlatformInstance = GetSROPlatformInstance(Target);

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
			"Serialization",
		});

		AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");
		AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");

		//ThirdParty include
		PrivateIncludePaths.AddRange(
			new string[]
			{
				Path.Combine(ThirdPartyRoot(), "protobuf/include"),
				Path.Combine(ThirdPartyRoot(), "grpc/include"),
				Path.Combine(ThirdPartyRoot(), "abseil/include"),
				Path.Combine(ModuleDirectory, "Private/pb")
			}
		);

		//ThirdParty Libraries
		ConfigurePlatform(Target.Platform.ToString(), Target.Configuration);
	}

	private SROPlatform GetSROPlatformInstance(ReadOnlyTargetRules Target)
	{
		var SROPlatformType = System.Type.GetType("SROPlatform_" + Target.Platform);
		if (SROPlatformType == null)
		{
			throw new BuildException("SRO does not support platform " + Target.Platform);
		}

		var PlatformInstance = Activator.CreateInstance(SROPlatformType) as SROPlatform;
		if (PlatformInstance == null)
		{
			throw new BuildException("SRO could not instantiate platform " + Target.Platform);
		}

		return PlatformInstance;
	}

	protected string ThirdPartyRoot()
	{
		return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/"));
	}

	private List<string> GrpcLibs = new List<string>
	{
		"grpc", "grpc++", "gpr", "upb", "address_sorting"
	};

	private List<string> ProtobufLibs = new List<string>
	{
		"protobuf"
	};

	private List<string> AbseilLibs = new List<string>
	{
		"absl_hash", "absl_city", "absl_wyhash", "absl_raw_hash_set", "absl_hashtablez_sampler",
		"absl_exponential_biased", "absl_statusor",
		"absl_bad_variant_access", "absl_status", "absl_cord", "absl_str_format_internal", "absl_synchronization",
		"absl_stacktrace",
		"absl_symbolize", "absl_debugging_internal", "absl_demangle_internal", "absl_graphcycles_internal",
		"absl_malloc_internal", "absl_time",
		"absl_strings", "absl_throw_delegate", "absl_strings_internal", "absl_base", "absl_spinlock_wait",
		"absl_int128", "absl_civil_time",
		"absl_time_zone", "absl_bad_optional_access", "absl_raw_logging_internal", "absl_log_severity",
	};

	private List<string> Re2Libs = new List<string>
	{
		"re2"
	};

	private bool ConfigurePlatform(string Platform, UnrealTargetConfiguration Configuration)
	{
		//turbolink thirdparty libraries root path
		string root = ThirdPartyRoot();

		//grpc
		foreach (var lib in GrpcLibs)
		{
			foreach (var arch in SROPlatformInstance.Architectures())
			{
				string fullPath = root + "grpc/" + "lib/" +
				                  SROPlatformInstance.LibrariesPath + arch +
				                  SROPlatformInstance.ConfigurationDir(Configuration) +
				                  SROPlatformInstance.LibraryPrefixName + lib + SROPlatformInstance.LibraryPostfixName;
				PublicAdditionalLibraries.Add(fullPath);
			}
		}

		//protobuf
		foreach (var lib in ProtobufLibs)
		{
			foreach (var arch in SROPlatformInstance.Architectures())
			{
				string fullPath = root + "protobuf/" + "lib/" +
				                  SROPlatformInstance.LibrariesPath + arch +
				                  SROPlatformInstance.ConfigurationDir(Configuration) +
				                  "lib" + lib + SROPlatformInstance.LibraryPostfixName;
				PublicAdditionalLibraries.Add(fullPath);
			}
		}

		//abseil
		foreach (var lib in AbseilLibs)
		{
			foreach (var arch in SROPlatformInstance.Architectures())
			{
				string fullPath = root + "abseil/" + "lib/" +
				                  SROPlatformInstance.LibrariesPath + arch +
				                  SROPlatformInstance.ConfigurationDir(Configuration) +
				                  SROPlatformInstance.LibraryPrefixName + lib + SROPlatformInstance.LibraryPostfixName;
				PublicAdditionalLibraries.Add(fullPath);
			}
		}

		//re2
		foreach (var lib in Re2Libs)
		{
			foreach (var arch in SROPlatformInstance.Architectures())
			{
				string fullPath = root + "re2/" + "lib/" +
				                  SROPlatformInstance.LibrariesPath + arch +
				                  SROPlatformInstance.ConfigurationDir(Configuration) +
				                  SROPlatformInstance.LibraryPrefixName + lib + SROPlatformInstance.LibraryPostfixName;
				PublicAdditionalLibraries.Add(fullPath);
			}
		}

		return false;
	}
}

public abstract class SROPlatform
{
	public virtual string ConfigurationDir(UnrealTargetConfiguration Configuration)
	{
		if (Configuration == UnrealTargetConfiguration.Debug || Configuration == UnrealTargetConfiguration.DebugGame)
		{
			return "Debug/";
		}
		else
		{
			return "Release/";
		}
	}

	public abstract string LibrariesPath { get; }
	public abstract List<string> Architectures();
	public abstract string LibraryPrefixName { get; }
	public abstract string LibraryPostfixName { get; }
}

public class SROPlatform_Win64 : SROPlatform
{
	public override string LibrariesPath
	{
		get { return "win64/"; }
	}

	public override List<string> Architectures()
	{
		return new List<string> { "" };
	}

	public override string LibraryPrefixName
	{
		get { return ""; }
	}

	public override string LibraryPostfixName
	{
		get { return ".lib"; }
	}
}

public class SROPlatform_Android : SROPlatform
{
	public override string LibrariesPath
	{
		get { return "android/"; }
	}

	public override List<string> Architectures()
	{
		return new List<string> { "armeabi-v7a/", "arm64-v8a/", "x86_64/" };
	}

	public override string LibraryPrefixName
	{
		get { return "lib"; }
	}

	public override string LibraryPostfixName
	{
		get { return ".a"; }
	}
}

public class SROPlatform_Linux : SROPlatform
{
	public override string LibrariesPath
	{
		get { return "linux/"; }
	}

	public override List<string> Architectures()
	{
		return new List<string> { "" };
	}

	public override string LibraryPrefixName
	{
		get { return "lib"; }
	}

	public override string LibraryPostfixName
	{
		get { return ".a"; }
	}
}

public class SROPlatform_PS5 : SROPlatform
{
	public override string LibrariesPath
	{
		get { return "ps5/"; }
	}

	public override List<string> Architectures()
	{
		return new List<string> { "" };
	}

	public override string LibraryPrefixName
	{
		get { return "lib"; }
	}

	public override string LibraryPostfixName
	{
		get { return ".a"; }
	}
}

public class SROPlatform_Mac : SROPlatform
{
	public override string ConfigurationDir(UnrealTargetConfiguration Configuration)
	{
		return "";
	}

	public override string LibrariesPath
	{
		get { return "mac/"; }
	}

	public override List<string> Architectures()
	{
		return new List<string> { "" };
	}

	public override string LibraryPrefixName
	{
		get { return "lib"; }
	}

	public override string LibraryPostfixName
	{
		get { return ".a"; }
	}
}

public class SROPlatform_IOS : SROPlatform
{
	public override string ConfigurationDir(UnrealTargetConfiguration Configuration)
	{
		return "";
	}

	public override string LibrariesPath
	{
		get { return "ios/"; }
	}

	public override List<string> Architectures()
	{
		return new List<string> { "" };
	}

	public override string LibraryPrefixName
	{
		get { return "lib"; }
	}

	public override string LibraryPostfixName
	{
		get { return ".a"; }
	}
}