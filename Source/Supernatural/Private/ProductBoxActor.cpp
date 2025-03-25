// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductBoxActor.h"
#include "Components/BoxComponent.h"

// Sets default values
AProductBoxActor::AProductBoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Box ∫Ÿ¿Ã±‚
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetBoxExtent(FVector(50));
	BoxComponent->SetCollisionProfileName(TEXT("Box"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(BoxComponent);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> tmpCube(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if(tmpCube.Succeeded()) Cube = tmpCube.Object;
	StaticMeshComponent->SetStaticMesh(Cube);
}

// Called when the game starts or when spawned
void AProductBoxActor::BeginPlay()
{
	Super::BeginPlay();

	BoxPhysicsOnOff(true);
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

}
void AProductBoxActor::SetCurrentStock(int32 InValue)
{
	this->CurrentStock = InValue;
}

void AProductBoxActor::BoxPhysicsOnOff(bool InValue)
{
    InValue ? BoxComponent->SetSimulatePhysics(true) : BoxComponent->SetSimulatePhysics(false);
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

int32 AProductBoxActor::CurrentStockGetter()
{
	return CurrentStock;
}
