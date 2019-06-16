// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class ArenaOfValorServerTarget : TargetRules   // Change this line as shown previously
{
       public ArenaOfValorServerTarget(TargetInfo Target) : base(Target)  // Change this line as shown previously
       {
        Type = TargetType.Server;
        ExtraModuleNames.AddRange( new string[] { "ArenaOfValorServerTarget" } );
       }

}

