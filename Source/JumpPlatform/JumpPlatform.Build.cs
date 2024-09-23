// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JumpPlatform : ModuleRules
{
	public JumpPlatform(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[]
        {
            this.Name
        });
    }
}
