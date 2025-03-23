// Fill out your copyright notice in the Description page of Project Settings.


#include "AITargetLocationActor.h"
#include "Components/BoxComponent.h"

// Sets default values
AAITargetLocationActor::AAITargetLocationActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(50));
	BoxComp->SetupAttachment(RootComponent);
}

void AAITargetLocationActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAITargetLocationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAITargetLocationActor::setBoxTag()
{
	
}

