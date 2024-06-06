// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProyectoIntermedio3 : ModuleRules
{
	public ProyectoIntermedio3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
