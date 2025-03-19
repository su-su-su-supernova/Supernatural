#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CProductDataTable.generated.h"

UENUM(BlueprintType)
enum class EProductType : uint8
{
	CEREAL = 0,
	MAX
};

USTRUCT()
struct FProductData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY(EditAnywhere, Category = "ProductData")
	EProductType ProductName;

	UPROPERTY(EditAnywhere, Category = "ProductData")
	FString ImagePath;

	UPROPERTY(EditAnywhere, Category = "ProductData")
	int32 CostPrice;

	UPROPERTY(EditAnywhere, Category = "ProductData")
	int32 SellingPrice;

	UPROPERTY(EditAnywhere, Category = "ProductData")
	int32 ShelfStock;

	UPROPERTY(EditAnywhere, Category = "ProductData")
	int32 StorageStock;

	UPROPERTY(EditAnywhere, Category = "ProductData")
	int32 BoxStock;

	UPROPERTY(EditAnywhere, Category = "ProductData")
	bool bIsDisplayed;

	UPROPERTY(EditAnywhere, Category = "ProductData")
	int32 MaxShelfStock;
};
