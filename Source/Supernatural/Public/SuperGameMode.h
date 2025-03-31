#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CProductDataTable.h"
#include "SuperAIController.h"
#include "Containers/Queue.h"
#include "CMonitorWidgetA.h"
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

	UFUNCTION(BlueprintCallable)
    int32 GenerateTicketNumber() { return CurrentTicketNumber; }


    void IncrementTicketCount() { CurrentTicketNumber++; }

	void SpawnAIHander();

	bool getIsSpawnAi();
	void CastCounterAndMonitorWidget();
    TQueue<int32> WaitingAIs;
private:

	UPROPERTY(VisibleAnywhere)
    int32 CurrentTicketNumber = 1;

	bool isSpawnAi = false;

	int32 TicketNumber = 1;
	int32 GameModeTicketNumber = 1;

	int32 TotalSales = 100000000;
	int32 CurrentTotalCost = 0;
	int32 CurrentInputCost = 0;

	bool bIsCalculating = false;

	class ACCounter* Counter;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UCMonitorWidgetA> MonitorWidgetFactory;
	class UCMonitorWidgetA* MonitorWidget;

public:
	int32 GetTotalSales() const { return TotalSales; }
	void SetTotalSales(int32 InTotalSales) { TotalSales = InTotalSales; }

	int32 GetCurrentTotalCost() const { return CurrentTotalCost; }
	void SetCurrentTotalCost(int32 InCurrentTotalCost);

	int32 GetCurrentInputCost() const { return CurrentInputCost; }
	void SetCurrentInputCost(int32 InCurrentInputCost);

	void SetIsCalculating(bool InIsCalculating)
	{
		bIsCalculating = InIsCalculating;

		if (bIsCalculating)
			UE_LOG(LogTemp, Error, TEXT(">>>>>>>> CALCULATE PRODUCT BEGIN <<<<<<<<"))
		else
			UE_LOG(LogTemp, Error, TEXT(">>>>>>>> CALCULATE PRODUCT END <<<<<<<<"))
	}
	bool GetIsCalculating() { return bIsCalculating; }

	class ACCounter* GetCounter() const {return Counter;}
};
