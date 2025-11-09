#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

class SortingLayerUtils
{
public:
	// Path to the sorting layers asset on disk
	static FString FilePath;

	// Returns the loaded DataTable containing sorting layers, or nullptr on failure
	static UDataTable* GetSortingLayersAsset();
};
