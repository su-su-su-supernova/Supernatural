#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EProductDivide.h"
#include "ProductSalesStandDataTable.generated.h"

USTRUCT(BlueprintType)
struct SUPERNATURAL_API FProductSalesStandDataTable : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EProductDivide ProductDivide;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMesh* Snack1;
};