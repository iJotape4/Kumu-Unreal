#pragma once

class SortingLayerUtils
{
public:
	UDataTable* SortingLayersAsset;
	static FString FilePath;
	
	static UDataTable* GetSortingLayersAsset();
};
