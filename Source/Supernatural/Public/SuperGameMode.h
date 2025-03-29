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

	void LoadProductDT(UScriptStruct* InStruct);


    FProductData* GetProductData(const FString& ProductName) const;

    FProductData* GetProductDataByIndex(int32 Index) const;

	void LoadProductData();

	int32 GenerateTicketNumber();

	void IncrementTicketCount();
	void IncrementGameModeTicketCount();
	int32 GenerateGameModeTicketNumber();
private:

	int32 TicketNumber = 1;
	int32 GameModeTicketNumber = 1;

	int32 TotalSales = 100000000;

public:
	int32 GetTotalSales() const { return TotalSales; }
	void SetTotalSales(int32 InTotalSales) { TotalSales = InTotalSales; }
};
