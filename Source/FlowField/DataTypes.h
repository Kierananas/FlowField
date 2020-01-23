#pragma once

#include "DataTypes.generated.h"


UENUM(BlueprintType)
enum class EGroundTypes : uint8 {

	NORMAL UMETA(DisplayName = "Normal"),
	DIFFICULT UMETA(DisplayName = "Difficult"),
	REALLYDIFFICULT UMETA(DisplayName = "Really Difficult"),
	IMPOSSIBLE UMETA(DisplayName = "Impossible"),
	NONE UMETA(DisplayName = "None"),

};
