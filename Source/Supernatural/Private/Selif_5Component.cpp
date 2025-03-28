// Fill out your copyright notice in the Description page of Project Settings.


#include "Selif_5Component.h"

// Sets default values for this component's properties
USelif_5Component::USelif_5Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//SetupMesh(1);

	// ...
}


// Called when the game starts
void USelif_5Component::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void USelif_5Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

