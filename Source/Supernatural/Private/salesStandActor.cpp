// Fill out your copyright notice in the Description page of Project Settings.


#include "salesStandActor.h"
#include "Components/BoxComponent.h"
#include "ProductSalesStandDataAsset.h"
#include "Components/StaticMeshComponent.h"
#include "EProductDivide.h"
#include "Selif_15Component.h"
#include "Selif_5Component.h"
#include "Selif_10Component.h"

AsalesStandActor::AsalesStandActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UProductSalesStandDataAsset>DataAssetFind(TEXT("/Script/Supernatural.ProductSalesStandDataAsset'/Game/HWL/Data/NewDataAsset.NewDataAsset'"));
	if (DataAssetFind.Succeeded()) {
		ProductSalesStandDataAsset = DataAssetFind.Object;
		CachedProducts = ProductSalesStandDataAsset->ProdctSalesStandDataTable;

	}
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(95, 25, 25));
	BoxComp->SetupAttachment(RootComponent);
	SelifBaseComp = CreateDefaultSubobject<USelif_BaseComponent>(TEXT("SelifBaseComp"));
	Comp5 = CreateDefaultSubobject<USelif_5Component>(TEXT("Comp5"));
	Comp10 = CreateDefaultSubobject<USelif_10Component>(TEXT("Comp10"));
	Comp15 = CreateDefaultSubobject<USelif_15Component>(TEXT("Comp15"));


	settingProductMesh(1);
	//settingProductMesh(2);
	//settingProductMesh(3);



}

void AsalesStandActor::BeginPlay()
{
	Super::BeginPlay();

	//for (int i = 0; i < 10; i++) {
	//	if (ProductMeshes[i] == nullptr) return;
	//ProductMeshes[i]->SetStaticMesh(CachedProducts[EProductDivide::Snack3].Snack1);
	//}
}

// Called every frame
void AsalesStandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AsalesStandActor::settingProductMesh(int32 v)
{
	int32 ProductNumber = 0;
	FName CompName = FName("");
	if (v == 1) { ProductNumber = 5; CompName = FName("SceneComp5"); }
	else if (v == 2) { ProductNumber = 10; CompName = FName("SceneComp10"); }
	else if (v == 3) { ProductNumber = 15; CompName = FName("SceneComp15"); }
	SceneComp = CreateDefaultSubobject<USceneComponent>(CompName);
	SceneComp->SetupAttachment(BoxComp);
	for (int i = 0; i < 5; i++) {
		FString ComponentName = FString::Printf(TEXT("Product%d"), i);
		UStaticMeshComponent* NewMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*ComponentName));
		if (!NewMesh)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create ProductMesh %d"), i);
			continue;
		}
		NewMesh->SetupAttachment(BoxComp);
		NewMesh->SetRelativeLocation(FVector(-85 + i * 12.0f, 0, 0));
		ProductMeshes.Add(NewMesh);
	}
	for (int i = 0; i < 5; i++) {
		if (ProductMeshes[i] == nullptr) return;
		ProductMeshes[i]->SetStaticMesh(CachedProducts[EProductDivide::Snack3].Snack1);
		//ProductMeshes[i]->SetVisibility(false);
	}
}

