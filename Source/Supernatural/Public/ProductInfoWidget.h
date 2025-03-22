// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProductInfoWidget.generated.h"

/**
 *
 */
UCLASS()
class SUPERNATURAL_API UProductInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ProductName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StorageStock;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ShelfStock;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BoxStock;

		UPROPERTY(meta = (BindWidget))
	class UTextBlock* CostPrice;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CostPriceSum;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ProductCount;


};
