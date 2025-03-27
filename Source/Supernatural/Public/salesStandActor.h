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
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;
	UPROPERTY(EditAnywhere)

	class UBoxComponent* TargetComp;
	class UStaticMeshComponent* MeshComp;

	class UProductSalesStandDataAsset* ProductSalesStandDataAsset;

	class UStaticMeshComponent* ProductMesh;
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

	//UFUNCTION(BlueprintCallable, Category = "SalesStand")

	void AddProduct(TArray<UStaticMeshComponent*>* TargetArray);

private:
	int32 ProductCountMax = 0;
	int32 CurrentProductCount = 0;
	EProductDivide CurrentProductType = EProductDivide::Snack1; // 기본값 설정
	int32 CurrentProductNumber = 0; // 기본값 설정

public:
	void SetMeshesForProductNumber(FString ProductType);



};
