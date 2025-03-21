#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CProductDataTable.h"
#include "SuperGameMode.generated.h"

class CProductDataTable;

UCLASS()
class SUPERNATURAL_API ASuperGameMode : public AGameModeBase
{
	GENERATED_BODY()
	ASuperGameMode();

protected:
	virtual void BeginPlay() override;

	/* Product Data Table */
public:
	//UPROPERTY(EditAnywhere, Category = "DataTable")
	class UDataTable* DTProduct;

	UPROPERTY(EditAnywhere)
	EProductType Type;

	TMap<FString, FProductData*> Product;

	//UPROPERTY(EditAnywhere, Category = "DataAsset")
	//class UCProductDataAsset* DAProduct;

	void LoadProductDT(UScriptStruct* InStruct);

	// void CreateProductDataAsset(UDataTable* InDT);

    FProductData* GetProductData(const FString& ProductName) const;

    FProductData* GetProductDataByIndex(int32 Index) const;

	void LoadProductData();
};
