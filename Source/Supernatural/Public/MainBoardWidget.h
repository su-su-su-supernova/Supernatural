// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProductInfoWidget.h"
#include "ProductBoxSpawner.h"
#include "CProductDataTable.h"
#include "ProductSellWidget.h"
#include "MainBoardWidget.generated.h"

/**
 *
 */
UCLASS()
class SUPERNATURAL_API UMainBoardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UMainBoardWidget(const FObjectInitializer& ObjectInitializer);


public:
	virtual void NativeConstruct() override;

public:
	class UProductInfoWidget* ProductInfoWidget;

	class UProductSellWidget* ProductSellWidget;

	TArray<FText>selectArrayProduct;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* WrapBox;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* ProductVerticalBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UProductInfoWidget> ProductInfoWidgetTool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UProductSellWidget> SellWidgettool;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<class AProductBoxSpawner> ProductBoxSpawner;

	UPROPERTY(meta = (BindWidget))
	class UButton* purchaseButton;
	UFUNCTION()
    void OnButtonClicked();
private:
	class ASuperGameMode* GameMode;
public:
	void SpawnProductBox(FText product);
	void SetVerticalBox(FText ProductName, FText CostPrice, FText CostPriceSum);
	void SetInfoWidget(TMap<FString, FProductData*> Product);





};
