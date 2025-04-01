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
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

public:
	class UProductInfoWidget* ProductInfoWidget;

	class UProductSellWidget* ProductSellWidget;

	TArray<EProductType>selectArrayProduct;

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
	class UTextBlock* Money;
	UPROPERTY(meta = (BindWidget))
	class UButton* SpawnerBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* purchaseButton;
	UFUNCTION()
    void OnButtonClicked();

	UFUNCTION()
    void OnSpwnerButtonClicked();
private:
	class ASuperGameMode* GameMode;
	class AProductBoxSpawner* productBox;
public:

	void SpawnProductBox(EProductType product);
	void SetVerticalBox(EProductType Enum, FText ProductName, FText ProductCount, FText CostPriceSum);
	void SetInfoWidget(TMap<EProductType, FProductData*> Product);

private:
	int32 PurchaseCost = 0;

	class USoundCue* MainBoardSound;
	class USoundCue* MainBoardSound2;

};
