// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProductSalesStandDataTable.h"
#include "salesStandActor.generated.h"

UCLASS()
class SUPERNATURAL_API AsalesStandActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AsalesStandActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	class UBoxComponent* BoxComp;
	class UStaticMeshComponent* MeshComp;

	class UProductSalesStandDataAsset* ProductSalesStandDataAsset;

	class UStaticMeshComponent* ProductMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<UStaticMeshComponent*> ProductMeshes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TMap<EProductDivide, FProductSalesStandDataTable> CachedProducts;

};
