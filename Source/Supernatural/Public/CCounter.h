#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <ProductSalesStandDataTable.h>
#include "CCounter.generated.h"

UCLASS()
class SUPERNATURAL_API ACCounter : public AActor
{
	GENERATED_BODY()
	
public:	
	ACCounter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Counter")
	class UStaticMeshComponent* CounterBody;

	UPROPERTY(EditAnywhere, Category = "Counter")
	class UStaticMesh* BodyMesh;

	UPROPERTY(EditAnywhere, Category = "Counter")
	class UBoxComponent* AISpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Counter Monitor")
	class UStaticMeshComponent* CounterMonitor;

	UPROPERTY(EditAnywhere, Category = "Counter Monitor")
	class UStaticMesh* MonitorMesh;

	UPROPERTY(EditAnywhere, Category = "Counter Monitor")
	class UMaterial* MonitorMat;
	
	UPROPERTY(EditAnywhere, Category = "Counter Monitor")
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, Category = "Casher")
	class UStaticMeshComponent* CasherBody;

	UPROPERTY(EditAnywhere, Category = "Casher")
	class UStaticMesh* CasherMesh;

	UPROPERTY(EditAnywhere, Category = "Calculate")
	class USkeletalMeshComponent* CreditCard;

	class UProductSalesStandDataAsset* ProductSalesStandDataAsset;

	UPROPERTY(EditAnywhere, Category = "Calculate")
	TArray<UStaticMeshComponent*> Products;

	bool bIsCustomerArrived = false;
	bool bIsProductsOnCounter = false;
	bool bCanCalculate = false;
	bool bIsCalculatingCompleted = false;

	int32 NPurchasedItems;
	int32 NCountedItems;
	int32 TotalCost;
	int32 InputCost;

	TArray<EProductDivide> ShoppingList;


public:
	bool GetIsCustomerArrived() const { return bIsCustomerArrived; }
	void SetIsCustomerArrived(bool bArrived) { bIsCustomerArrived = bArrived; }

	bool GetIsProductsOnCounter() const { return bIsProductsOnCounter; }
	void SetIsProductsOnCounter(bool bOnCounter) { bIsProductsOnCounter = bOnCounter; }

	bool GetCanCalculate() const { return bCanCalculate; }
	void SetCanCalculate(bool canCalculate) { bCanCalculate = canCalculate; }

	int32 GetNPurchasedItems() const { return NPurchasedItems; }
	void SetNPurchasedItems(int32 PurchasedItems) { NPurchasedItems = PurchasedItems; }

	int32 GetNCountedItems() const { return NCountedItems; }
	void SetNCountedItems(int32 CountedItems) { NCountedItems = CountedItems; }

	int32 GetTotalCost() const { return TotalCost; }
	void SetTotalCost(int32 Cost) { TotalCost = Cost; }

	int32 GetInputCost() const { return InputCost; }
	void SetInputCost(int32 Cost) { InputCost = Cost; }

	TArray<EProductDivide> GetShoppingList() const { return ShoppingList; }
	void SetShoppingList(const TArray<EProductDivide>& InShoppingList) { ShoppingList = InShoppingList; }


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TMap<EProductDivide, FProductSalesStandDataTable> CachedProducts;

	UFUNCTION()
	void OnAIBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void PlaceProductOnCounter();
	void SetVisibilityOn(class UStaticMeshComponent* InComp);
};
