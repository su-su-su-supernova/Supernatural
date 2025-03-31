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

	TMap<EProductType, FProductData*> Product;

	void LoadProductDT(UScriptStruct* InStruct);


	FProductData* GetProductData(EProductType ProductType) const;

    FProductData* GetProductDataByIndex(int32 Index) const;

	void LoadProductData();

	int32 GenerateTicketNumber();

	void IncrementTicketCount();
	void IncrementGameModeTicketCount();
	int32 GenerateGameModeTicketNumber();
	void CastCounter();

private:
	int32 TicketNumber = 1;
	int32 GameModeTicketNumber = 1;

	int32 TotalSales = 100000000;
	int32 CurrentCheckoutTotal = 0;
	int32 CurrentInputTotal = 0;

	bool bIsCalculating = false;

	class ACCounter* Counter;

public:
	int32 GetTotalSales() const { return TotalSales; }
	void SetTotalSales(int32 InTotalSales) { TotalSales = InTotalSales; }

	int32 GetCurrentCheckoutTotal() const { return CurrentCheckoutTotal; }
	void SetCurrentCheckoutTotal(int32 InCurrentCheckoutTotal) { CurrentCheckoutTotal = InCurrentCheckoutTotal; }

	int32 GetCurrentInputTotal() const { return CurrentInputTotal; }
	void SetCurrentInputTotal(int32 InCurrentInputTotal) { CurrentInputTotal = InCurrentInputTotal; }

	void SetIsCalculating(bool InIsCalculating) 
	{ 
		bIsCalculating = InIsCalculating; 

		if (bIsCalculating)
			UE_LOG(LogTemp, Error, TEXT(">>>>>>>> CALCULATE PRODUCT BEGIN <<<<<<<<"))
		else
			UE_LOG(LogTemp, Error, TEXT(">>>>>>>> CALCULATE PRODUCT END <<<<<<<<"))
	}

	class ACCounter* GetCounter() const {return Counter;}
};
