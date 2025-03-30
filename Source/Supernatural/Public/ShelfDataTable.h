// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EProductDivide.h"
#include "ShelfDataTable.generated.h"

USTRUCT(BlueprintType)
struct SUPERNATURAL_API FShelfDataTable : public FTableRowBase
{
	GENERATED_BODY()


public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EProductDivide ProductType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Dist;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 LimitCount;
};