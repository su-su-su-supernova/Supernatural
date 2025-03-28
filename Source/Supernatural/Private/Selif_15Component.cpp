// Fill out your copyright notice in the Description page of Project Settings.


#include "Selif_15Component.h"

// Sets default values for this component's properties
USelif_15Component::USelif_15Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//SetupMesh(3);

	// ...
}


// Called when the game starts
void USelif_15Component::BeginPlay()
{
	Super::BeginPlay();

	//InputMesh();
	// ...



}


// Called every frame
void USelif_15Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USelif_15Component::InputMesh()
{
	for (int i = 0; i < 15; i++) {
		if (ProductMeshes[i] == nullptr) return;
		ProductMeshes[i]->SetStaticMesh(CachedProducts[EProductDivide::Snack3].Snack1);
		//ProductMeshes[i]->SetVisibility(false);
	}
}

void USelif_15Component::setVisible()
{
	ProductMeshes[CurrentProductCount]->SetVisibility(true);
	CurrentProductCount++;
}

