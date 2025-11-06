#include "SortingLayerUtils.h"

#include "EngineUtils.h"

FString SortingLayerUtils::FilePath = FPaths::ProjectContentDir() + TEXT(
		"ThirdParty/2D_Tools/SortingLayers/DT_SortingLayers.uasset");


UDataTable* SortingLayerUtils::GetSortingLayersAsset()
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	
	if (PlatformFile.FileExists(*FilePath))
	{
		FString AssetLongPath = FPackageName::FilenameToLongPackageName(FilePath);
		FString AssetObjectPath = AssetLongPath + TEXT(".") + FPaths::GetBaseFilename(FilePath);
		UDataTable* DataTable = LoadObject<UDataTable>(nullptr, *AssetObjectPath);
		if (DataTable)
		{
			UE_LOG(LogTemp, Warning, TEXT("Loaded DataTable: %s"), *AssetObjectPath);
			return DataTable;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load DataTable at: %s"), *AssetObjectPath);
			return nullptr;
		}
	}
	else
	{
		// File does not exist
		UE_LOG(LogTemp, Error, TEXT("File not found at: %s"), *FilePath);
		return nullptr;
	}

}
