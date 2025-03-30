// Fill out your copyright notice in the Description page of Project Settings.


#include "salesStandActor.h"
#include "Components/BoxComponent.h"
#include "ProductSalesStandDataAsset.h"
#include "Components/StaticMeshComponent.h"
#include "EProductDivide.h"
AsalesStandActor::AsalesStandActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UProductSalesStandDataAsset>DataAssetFind(TEXT("/Script/Supernatural.ProductSalesStandDataAsset'/Game/HWL/Data/DA_Mesh.DA_Mesh'"));
	if (DataAssetFind.Succeeded()) {
		ProductSalesStandDataAsset = DataAssetFind.Object;
		CachedProducts = ProductSalesStandDataAsset->ProdctSalesStandDataTable;
	}
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(95, 25, 25));
	BoxComp->SetupAttachment(RootComponent);

	TargetComp = CreateDefaultSubobject<UBoxComponent>(TEXT("TargetComp"));
	TargetComp->SetBoxExtent(FVector(95, 25, 25));
	TargetComp->SetRelativeLocation(FVector(-54, 117, 29));
	TargetComp->SetCollisionProfileName(TEXT("ProductTarget"));
	TargetComp->SetupAttachment(RootComponent);

	SceneComp5 = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp5"));
	SceneComp5->SetupAttachment(BoxComp);
	SceneComp10 = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp10"));
	SceneComp10->SetupAttachment(BoxComp);
	SceneComp15 = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp15"));
	SceneComp15->SetupAttachment(BoxComp);

	settingProductMesh(3);
	settingProductMesh(2);
	settingProductMesh(1);



}

void AsalesStandActor::BeginPlay()
{
	Super::BeginPlay();

}

void AsalesStandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AsalesStandActor::settingProductMesh(int32 v)
{

	int32 ProductNumber = 0;
	USceneComponent* TargetSceneComp = nullptr;
	EProductDivide ProductType = EProductDivide::Shelf5;
	float ProductDistance = 0;
	if (CurrentProductCount > 0) v = ProductCountMax;

	if (v == 1) { ProductNumber = 5; TargetSceneComp = SceneComp5; ProductType = EProductDivide::Shelf5; ProductDistance = 40.5f; }
	else if (v == 2) { ProductNumber = 10; TargetSceneComp = SceneComp10; ProductType = EProductDivide::Shelf10; ProductDistance = 18.0f; }
	else if (v == 3) { ProductNumber = 15; TargetSceneComp = SceneComp15; ProductType = EProductDivide::Shelf15; ProductDistance = 12.0f; }
	else return;
	decideProductType(ProductNumber, TargetSceneComp, ProductType, ProductDistance);
}

void AsalesStandActor::decideProductType(int32 ProductNumber, USceneComponent* TargetSceneComp, EProductDivide ProductType, float ProductDistance)
{
	// ??? ????
	static int32 j = 0;
	TArray<UStaticMeshComponent*>* TargetArray = nullptr;

	// ProductNumber?? ???? ?????? ?עק ????
	if (ProductNumber == 5) TargetArray = &ProductMeshes5;
	else if (ProductNumber == 10) TargetArray = &ProductMeshes10;
	else if (ProductNumber == 15) TargetArray = &ProductMeshes15;

	// ??? ???? ?? ?עק?? ???
	for (int i = 0; i < ProductNumber; i++) {
		FString ComponentName = FString::Printf(TEXT("Product%d"), j++);
		UStaticMeshComponent* NewMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*ComponentName));
		if (!NewMesh)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create ProductMesh %d"), i);
			continue;
		}
		NewMesh->SetupAttachment(TargetSceneComp);
		NewMesh->SetRelativeLocation(FVector(-85 + i * ProductDistance, 0, -20));
		NewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		if (ProductType == EProductDivide::Shelf5)
			NewMesh->SetRelativeScale3D(FVector(0.7));
		TargetArray->Add(NewMesh);
	}
}

bool AsalesStandActor::SetMeshesForProductNumber(FProductData* ProductData)
{
	//Tags.Push(*ProductName);
	//Tags.Add(TEXT("Cake"));
	//for (auto a : Tags) {
	//	Tags.RemoveAt(Tags.Find(TEXT("Cake")));
	//}

	TArray<UStaticMeshComponent*>* TargetArray = nullptr;
	EProductType ProductType= ProductData->ProductEnum;
	int32 ProductNumber = ProductData->MaxShelfStock;

	if (ProductData->MaxShelfStock == 5) {
		TargetArray = &ProductMeshes5;
	}
	else if (ProductData->MaxShelfStock == 10) {
		TargetArray = &ProductMeshes10;
	}
	else if (ProductData->MaxShelfStock == 15) {
		TargetArray = &ProductMeshes15;
	}


	if (CurrentProductCount == 0)
	{
		CurrentProductNumber = ProductNumber;
		CurrentProductType = ProductType;
		ProductCountMax = ProductNumber;

		for (int i = 0; i < TargetArray->Num(); i++) {
			if ((*TargetArray)[i] && CachedProducts.Contains(ProductType) && CachedProducts[ProductType].MeshData)
			{
				(*TargetArray)[i]->SetStaticMesh(CachedProducts[ProductType].MeshData);
				(*TargetArray)[i]->SetVisibility(false);
			}
		}
		AddProduct(TargetArray);
	}
	else if (CurrentProductType == ProductType) // ProductNumber ?? ????
	{
		AddProduct(TargetArray);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ignoring SetMeshesForProductNumber: Different ProductNumber or ProductType"));
	}

	return bIsFull;
}

void AsalesStandActor::AddProduct(TArray<UStaticMeshComponent*>* TargetArray)
{
	UE_LOG(LogTemp, Warning, TEXT("[HW] CurrentProductCount : %d"), CurrentProductCount);

	if (CurrentProductCount >= ProductCountMax)
	{
		bIsFull = true;
		return;
	}

	(*TargetArray)[CurrentProductCount]->SetVisibility(true);
	CurrentProductCount++;

	bIsFull = false;
}