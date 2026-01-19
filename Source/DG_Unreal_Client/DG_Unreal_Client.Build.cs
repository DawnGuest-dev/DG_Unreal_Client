// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class DG_Unreal_Client : ModuleRules
{
	public DG_Unreal_Client(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"DG_Unreal_Client",
			"DG_Unreal_Client/Variant_Strategy",
			"DG_Unreal_Client/Variant_Strategy/UI",
			"DG_Unreal_Client/Variant_TwinStick",
			"DG_Unreal_Client/Variant_TwinStick/AI",
			"DG_Unreal_Client/Variant_TwinStick/Gameplay",
			"DG_Unreal_Client/Variant_TwinStick/UI"
		});

		string ThirdPartyPath = Path.Combine(ModuleDirectory, "../ThirdParty");
		string ProtobufPath = Path.Combine(ThirdPartyPath, "Protobuf");
		string LibPath = Path.Combine(ProtobufPath, "Libs");
		
		string FlatBuffersPath = Path.Combine(ModuleDirectory, "../ThirdParty/FlatBuffers");
		
		
		// 헤더 경로 추가
		PublicIncludePaths.Add(Path.Combine(ProtobufPath, "Includes"));
		PublicIncludePaths.Add(FlatBuffersPath);

		// 라이브러리 추가 (Windows 기준)
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// [추가] 정의되지 않은 식별자 경고를 끕니다 (C4668 해결)
			CppCompileWarningSettings.UndefinedIdentifierWarningLevel = WarningLevel.Off;
    
			// [추가] Protobuf는 C++ 예외 처리가 필요할 수 있습니다
			bEnableExceptions = true;
			
			if (Directory.Exists(LibPath))
			{
				// Libs 폴더에 있는 모든 .lib 파일을 찾아서 등록합니다.
				// Protobuf와 Abseil 라이브러리가 모두 포함됩니다.
				string[] Libs = Directory.GetFiles(LibPath, "*.lib");
                
				foreach (string Lib in Libs)
				{
					PublicAdditionalLibraries.Add(Lib);
				}
			}
		}
	}
}
