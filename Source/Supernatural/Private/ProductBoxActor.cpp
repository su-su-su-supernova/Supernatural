// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductBoxActor.h"

// Sets default values
AProductBoxActor::AProductBoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProductBoxActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProductBoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProductBoxActor::SetBoxInfo(FName PdName, FName ImgPath, int32 CtPrice, int32 OdStock)
{
	this->ProductName = PdName;
	this->ImagePath = ImgPath;
	this->CostPrice = CtPrice;
	this->OrderStock = OdStock;

	UE_LOG(LogTemp, Warning, TEXT("%d"), CostPrice);
}
FName AProductBoxActor::ProductNameGetter()
{
	return ProductName;
}

FName AProductBoxActor::ImagePathGetter()
{
	return ImagePath;
}

int32 AProductBoxActor::CostPriceGetter()
{
	return CostPrice;
}

int32 AProductBoxActor::OrderStockGetter()
{
	return OrderStock;
}
