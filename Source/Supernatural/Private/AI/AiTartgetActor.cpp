// Fill out your copyright notice in the Description page of Project Settings.


#include "AiTartgetActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAiTartgetActor::AAiTartgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(50));
	BoxComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AAiTartgetActor::BeginPlay()
{
	Super::BeginPlay();

	//Tags.Add(FName(TEXT("Coke")));
}

// Called every frame
void AAiTartgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

