#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EProductType.generated.h"

UENUM(BlueprintType)
enum class EProductType : uint8
{
	CEREAL = 0,
	COKE,
	TEA,
	MAX
};