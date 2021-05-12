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

		string dir = @"E:\Arbeit_Forschungszentrum\Repo\JPSvisUE\Extern"; 

		PublicIncludePaths.Add(Path.Combine(dir,"libiconv", "Header"));
		PublicAdditionalLibraries.Add(Path.Combine(dir, "libiconv", "libiconv.lib"));

		PublicIncludePaths.Add(Path.Combine(dir, "DXF", "Header"));
		PublicAdditionalLibraries.Add(Path.Combine(dir, "DXF", "libdxfrw.lib"));
	}
}
