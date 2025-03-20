// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProductSellWidget.generated.h"

/**
 *
 */
UCLASS()
class SUPERNATURAL_API UProductSellWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ProductName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CostPriceSum;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ProductCount;
};
