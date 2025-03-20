// Fill out your copyright notice in the Description page of Project Settings.


#include "salesStandActor.h"
#include "Components/BoxComponent.h"
#include "ProductSalesStandDataAsset.h"
#include "Components/StaticMeshComponent.h"
#include "EProductDivide.h"

// Sets default values
AsalesStandActor::AsalesStandActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(95, 25, 25));
	BoxComp->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UProductSalesStandDataAsset>DataAssetFind(TEXT("/Script/Supernatural.ProductSalesStandDataAsset'/Game/HWL/Data/NewDataAsset.NewDataAsset'"));
	if (DataAssetFind.Succeeded()) {
		ProductSalesStandDataAsset = DataAssetFind.Object;
		CachedProducts = ProductSalesStandDataAsset->ProdctSalesStandDataTable;

	}


	for (int i = 0; i < 10; i++) {
		FString ComponentName = FString::Printf(TEXT("Product%d"), i);
		UStaticMeshComponent* NewMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*ComponentName));
		if (!NewMesh)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create ProductMesh %d"), i);
			continue;
		}
		NewMesh->SetupAttachment(BoxComp);
		NewMesh->SetRelativeLocation(FVector(i * 10.0f, 0, 0));
		ProductMeshes.Add(NewMesh);

	}

}

// Called when the game starts or when spawned
void AsalesStandActor::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < 10; i++) {
		if (ProductMeshes[i] == nullptr) return;
	ProductMeshes[i]->SetStaticMesh(CachedProducts[EProductDivide::Snack3].Snack1);
	}
}

// Called every frame
void AsalesStandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

