// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProductBoxActor.generated.h"

UCLASS()
class SUPERNATURAL_API AProductBoxActor : public AActor
{
	GENERATED_BODY()

private:
	FName ProductName;
	FName ImagePath;
	int32 CostPrice;
	int32 OrderStock;
	int32 CurrentStock;

	class UBoxComponent* BoxComponent;
	class UStaticMeshComponent* StaticMeshComponent;
	class UStaticMesh* Cube;

public:
	FName ProductNameGetter();
	FName ImagePathGetter();
	int32 CostPriceGetter();
	int32 OrderStockGetter();
	int32 CurrentStockGetter();

public:
	// Sets default values for this actor's properties
	AProductBoxActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetBoxInfo(FName ProductName, FName ImagePath, int32 CostPrice, int32 OrderStock);
	void SetCurrentStock(int32 InValue);
	void BoxPhysicsOnOff(bool InValue);
};
