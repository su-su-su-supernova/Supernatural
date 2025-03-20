// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductBoxSpawner.h"
#include "Components/ArrowComponent.h"
#include "ProductBoxActor.h"

// Sets default values
AProductBoxSpawner::AProductBoxSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("sceneComp"));
	SetRootComponent(SceneComp);
	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	ArrowComp->SetRelativeRotation(FRotator(90, 0, 0));
	ArrowComp->SetupAttachment(SceneComp);

}

// Called when the game starts or when spawned
void AProductBoxSpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->SpawnActor<AProductBoxActor>(BoxClass, ArrowComp->GetComponentTransform());

}

// Called every frame
void AProductBoxSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProductBoxSpawner::SpawnBoxHandler(FName a, FName ImagePath, int32 CostPrice, int32 OrderStock)
{
	//AProductBoxActor* ProductBoxActor = Cast<AProductBoxActor>(BoxClass);
	if(ProductBoxActor)
	GetWorld()->SpawnActor<AProductBoxActor>(BoxClass, ArrowComp->GetComponentTransform());
}

