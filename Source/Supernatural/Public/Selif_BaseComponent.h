// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProductSalesStandDataTable.h"
#include "EProductDivide.h"
#include "Selif_BaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERNATURAL_API USelif_BaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USelif_BaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	class AsalesStandActor* StandActor;

	void SetupMesh(int32 v);

	class UStaticMeshComponent* MeshComp;

	class UProductSalesStandDataAsset* ProductSalesStandDataAsset;

	class UStaticMeshComponent* ProductMesh;

	class USceneComponent* SceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<UStaticMeshComponent*> ProductMeshes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TMap<EProductDivide, FProductSalesStandDataTable> CachedProducts;



};
