// Fill out your copyright notice in the Description page of Project Settings.


#include "Selif_BaseComponent.h"
#include "ProductSalesStandDataAsset.h"
#include "salesStandActor.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
USelif_BaseComponent::USelif_BaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UProductSalesStandDataAsset>DataAssetFind(TEXT("/Script/Supernatural.ProductSalesStandDataAsset'/Game/HWL/Data/NewDataAsset.NewDataAsset'"));
	if (DataAssetFind.Succeeded()) {
		ProductSalesStandDataAsset = DataAssetFind.Object;
		CachedProducts = ProductSalesStandDataAsset->ProdctSalesStandDataTable;

	}
	// ...
}


// Called when the game starts
void USelif_BaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void USelif_BaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USelif_BaseComponent::SetupMesh(int32 v)
{
	StandActor = Cast<AsalesStandActor>(GetOwner());
	if(!StandActor)return;
	int32 ProductNumber=0;
	FName CompName = FName("");
	if (v == 1) { ProductNumber = 5; CompName = FName("SceneComp5"); }
	else if (v == 2) { ProductNumber = 10; CompName = FName("SceneComp10"); }
	else if (v == 3) { ProductNumber = 15; CompName = FName("SceneComp15"); }
	else return;
	SceneComp = CreateDefaultSubobject<USceneComponent>(CompName);
	SceneComp->SetupAttachment(StandActor->BoxComp);

	for (int i = 0; i < ProductNumber; i++) {
		FString ComponentName = FString::Printf(TEXT("Product%d"), i);
		UStaticMeshComponent* NewMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*ComponentName));
		if (!NewMesh)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create ProductMesh %d"), i);
			continue;
		}
		NewMesh->SetupAttachment(StandActor->BoxComp);
		NewMesh->SetRelativeLocation(FVector(-85+i * 12.0f, 0, 0));
		ProductMeshes.Add(NewMesh);
	}
	for (int i = 0; i < 15; i++) {
		if (ProductMeshes[i] == nullptr) return;
		ProductMeshes[i]->SetStaticMesh(CachedProducts[EProductDivide::Snack3].Snack1);
		//ProductMeshes[i]->SetVisibility(false);
	}
}

