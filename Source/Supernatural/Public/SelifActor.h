// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "salesStandActor.h"
#include "CLineTraceZone.h"
#include "SelifActor.generated.h"

UCLASS()
class SUPERNATURAL_API ASelifActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASelifActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class AsalesStandActor* salesStandActor;
	//class UBoxComponent* BoxComp;
	class ACLineTraceZone* CLineTraceZone;
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TSubclassOf<AsalesStandActor>salesStandActorTool;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TSubclassOf<ACLineTraceZone>LineTraceZoneTool;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComp;

	TArray<float> z_loacation = {45,95,150};

};
