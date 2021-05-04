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


		string dir = @"E:\Arbeit_Forschungszentrum\DXF3\libdxfrw-master";

		PublicIncludePaths.Add(Path.Combine(dir, "src"));
		PublicAdditionalLibraries.Add(Path.Combine(dir, "vs2013","x64", "Release", "libdxfrw.lib"));

		//PublicIncludePaths.Add(@"E:\Arbeit_Forschungszentrum\Repo\JPSvisUE\libiconv\1.9.2\libiconv-1.9.2\include");
	}
}
