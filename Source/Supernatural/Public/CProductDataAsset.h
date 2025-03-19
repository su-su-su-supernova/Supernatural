#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CProductDataTable.h"
#include "CProductDataAsset.generated.h"

UCLASS()
class SUPERNATURAL_API UCProductDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EProductType, FProductData> Product;
};
