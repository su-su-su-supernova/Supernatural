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
	MainSceneComp= CreateDefaultSubobject<USceneComponent>(TEXT("MainSceneComp"));
	MainSceneComp->SetupAttachment(RootComponent);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(95, 25, 25));
	BoxComp->SetupAttachment(MainSceneComp);

	TargetComp = CreateDefaultSubobject<UBoxComponent>(TEXT("TargetComp"));
	TargetComp->SetBoxExtent(FVector(25));
	TargetComp->SetCollisionProfileName(TEXT("ProductTarget"));
	TargetComp->SetupAttachment(BoxComp);

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
	static int32 j = 0;
	TArray<UStaticMeshComponent*>* TargetArray = nullptr;

	if (ProductNumber == 5) TargetArray = &ProductMeshes5;
	else if (ProductNumber == 10) TargetArray = &ProductMeshes10;
	else if (ProductNumber == 15) TargetArray = &ProductMeshes15;

	for (int i = 0; i < ProductNumber; i++) {
		FString ComponentName = FString::Printf(TEXT("Product%d"), j++);
		UStaticMeshComponent* NewMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*ComponentName));
		if (!NewMesh)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create ProductMesh %d"), i);
			continue;
		}
		NewMesh->SetupAttachment(TargetSceneComp);
		NewMesh->SetRelativeLocation(FVector(-85 + i * ProductDistance, 0, -25));
		NewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		if (ProductType == EProductDivide::Shelf5)
			NewMesh->SetRelativeScale3D(FVector(0.7));
		TargetArray->Add(NewMesh);
	}
}

bool AsalesStandActor::SetMeshesForProductNumber(FProductData* ProductData)
{
	if (ProductData == nullptr) return false;
	SProductData = ProductData;
	if (TargetComp->ComponentTags.Num()==0) {
		TargetComp->ComponentTags.Push(*UEnum::GetValueAsString(ProductData->ProductEnum));
	}

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
	else {
		return false;
	}

	if (CurrentProductCount == 0)
	{
		CurrentProductNumber = ProductNumber;
		CurrentProductType = ProductType;
		ProductCountMax = ProductNumber;
		if (TargetArray==nullptr)return false;
		for (int i = 0; i < TargetArray->Num(); i++) {
			if ((*TargetArray)[i] && CachedProducts.Contains(ProductType) && CachedProducts[ProductType].MeshData)
			{
				(*TargetArray)[i]->SetStaticMesh(CachedProducts[ProductType].MeshData);
				(*TargetArray)[i]->SetVisibility(false);
			}
		}
		AddProduct(TargetArray);
	}
	else if (CurrentProductType == ProductType)
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

FProductData* AsalesStandActor::RemoveProduct()
{

	// 적절한 TargetArray 선택
	TArray<UStaticMeshComponent*>* TargetArray = nullptr;
	if (CurrentProductNumber == 5) TargetArray = &ProductMeshes5;
	else if (CurrentProductNumber == 10) TargetArray = &ProductMeshes10;
	else if (CurrentProductNumber == 15) TargetArray = &ProductMeshes15;

	// 제품 제거 (마지막 제품 숨기기)
	CurrentProductCount--;
	ProductMesh = (*TargetArray)[CurrentProductCount];
	if (ProductMesh)
	{
		ProductMesh->SetVisibility(false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[HW] ProductMesh at index %d is null"), CurrentProductCount);
	}

	// 상태 업데이트
	bIsFull = false;

	// 모든 제품이 제거된 경우 초기화
	if (CurrentProductCount == 0)
	{
		// 현재 제품 타입을 문자열로 변환
		FString ProductTypeString = UEnum::GetValueAsString(CurrentProductType);

		// Tags에서 해당 제품 타입 제거
		TargetComp->ComponentTags.RemoveSingle(*ProductTypeString);

		// 상태 초기화
		CurrentProductNumber = 0;
		CurrentProductType = EProductType::MAX; // 열거형의 기본값으로 가정
	}
	UE_LOG(LogTemp, Warning, TEXT("[HW] Product removed. CurrentProductCount: %d"), CurrentProductCount);
	return SProductData;
}
