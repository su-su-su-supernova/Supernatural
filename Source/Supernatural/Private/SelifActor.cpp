// Fill out your copyright notice in the Description page of Project Settings.


#include "SelifActor.h"
#include "salesStandActor.h"
#include "CLineTraceZone.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASelifActor::ASelifActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASelifActor::BeginPlay()
{
	Super::BeginPlay();

	for(int i=0;i<3;i++){
		salesStandActor = GetWorld()->SpawnActor<AsalesStandActor>(salesStandActorTool);
	// 2. 스폰된 엑터를 this의 자식으로 붙이기
	if (salesStandActor)
	{
		salesStandActor->SetActorRelativeLocation(FVector(0,0, z_loacation[i]));
		salesStandActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}

	}
	CLineTraceZone = GetWorld()->SpawnActor<ACLineTraceZone>(LineTraceZoneTool);
	CLineTraceZone->SetActorRelativeLocation(FVector(0,57,100));
	CLineTraceZone->SetActorRelativeScale3D(FVector(3,1,2.25));
	CLineTraceZone->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called every frame
void ASelifActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

