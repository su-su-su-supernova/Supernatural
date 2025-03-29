#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

};
