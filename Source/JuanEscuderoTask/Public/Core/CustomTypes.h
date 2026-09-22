#pragma once

#include "CoreMinimal.h"
#include "CustomTypes.generated.h"

UENUM(BlueprintType)
enum class EMatchResult : uint8
{
	None,
	Won,
	Lost
};
