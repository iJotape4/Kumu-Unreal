#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FSortingLayers : uint8
{
	BACKGROUND = 0 UMETA(DisplayName = "BACKGROUND"),
	DEFAULT = 10  UMETA(DisplayName = "DEFAULT"),
	STAR_PARTICLE_LAYER = 20 UMETA(DisplayName = "STAR PARTICLE LAYER"),
	CLIENT = 30 UMETA(DisplayName = "CLIENT"),
	COOKING_STAND = 40 UMETA(DisplayName = "Cooking Stand"),
	FOOD_TABLE = 50 UMETA(DisplayName = "Food Table"),
	DRAGGABLE = 60 UMETA(DisplayName = "Draggable"),
	MONKEY_LAYOUT = 70 UMETA(DisplayName = "Monkey Layout"),
	DRAGGED = 80 UMETA(DisplayName = "Dragged"),
	UI = 90 UMETA(DisplayName = "UI"),
};