// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ShelfDataTable.h"
#include "ShelfDataTable.h"
#include "ShelfDataAsset.generated.h"

/**
 *
 */
UCLASS()
class SUPERNATURAL_API UShelfDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EProductDivide, FShelfDataTable>ShelfDataAsset;
};
