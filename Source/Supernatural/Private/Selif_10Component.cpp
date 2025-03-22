// Fill out your copyright notice in the Description page of Project Settings.


#include "Selif_10Component.h"

// Sets default values for this component's properties
USelif_10Component::USelif_10Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//SetupMesh(2);

	// ...
}


// Called when the game starts
void USelif_10Component::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void USelif_10Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

