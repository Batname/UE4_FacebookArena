// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FacebookArenaTarget : TargetRules
{
	public FacebookArenaTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("FacebookArena");
		ExtraModuleNames.Add("FacebookArenaSinglePlayer");
	}
}
