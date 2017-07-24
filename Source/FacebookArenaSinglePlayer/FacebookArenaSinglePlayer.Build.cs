// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FacebookArenaSinglePlayer : ModuleRules
{
	public FacebookArenaSinglePlayer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		//The path for the header files
		PublicIncludePaths.AddRange(new string[] {"FacebookArenaSinglePlayer/Public"});
		
		//The path for the source files
		PrivateIncludePaths.AddRange(new string[] {"FacebookArenaSinglePlayer/Private"});
	}
}
