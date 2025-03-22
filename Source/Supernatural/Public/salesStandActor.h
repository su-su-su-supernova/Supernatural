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

	class USelif_5Component* Comp5;
	class USelif_10Component* Comp10;
	class USelif_15Component* Comp15;
	class USelif_BaseComponent* SelifBaseComp;
	class USceneComponent* SceneComp5;
	class USceneComponent* SceneComp10;
	class USceneComponent* SceneComp15;


	UPROPERTY()
	TArray<UStaticMeshComponent*> ProductMeshes5;

	UPROPERTY()
	TArray<UStaticMeshComponent*> ProductMeshes10;

	UPROPERTY()
	TArray<UStaticMeshComponent*> ProductMeshes15;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TMap<EProductDivide, FProductSalesStandDataTable> CachedProducts;

private:
	void settingProductMesh(int32 v);
	void decideProductType(int32 ProductNumber, USceneComponent* TargetSceneComp, EProductDivide ProductType, float ProductDistance);
	// 새 함수 선언
	UFUNCTION(BlueprintCallable, Category = "SalesStand")
	void SetMeshesForProductNumber(int32 ProductNumber, EProductDivide ProductType);

};
