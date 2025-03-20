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

public:
	FName ProductNameGetter();
	FName ImagePathGetter();
	int32 CostPriceGetter();
	int32 OrderStockGetter();

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

};
