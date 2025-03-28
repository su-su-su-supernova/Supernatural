// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProductSalesStandDataTable.h"
#include "EProductDivide.h"
#include "ProductSalesStandDataAsset.generated.h"

/**
 *
 */
UCLASS()
class SUPERNATURAL_API UProductSalesStandDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EProductDivide, FProductSalesStandDataTable>ProdctSalesStandDataTable;
};
