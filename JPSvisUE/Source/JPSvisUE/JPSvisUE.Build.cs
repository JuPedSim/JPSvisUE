// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class JPSvisUE : ModuleRules
{
	public JPSvisUE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","SlateCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });


		string dir = @"E:\Arbeit_Forschungszentrum\Repo\JPSvisUE\DXF";

		PublicIncludePaths.Add(Path.Combine(dir, "src"));

		// Add any import libraries or static libraries
		PublicAdditionalLibraries.Add(Path.Combine(dir, "vs2013","Debug", "libdxfrw.lib"));


		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
