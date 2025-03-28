// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductInfoWidget.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ProductBoxSpawner.h"
#include "SuperGameMode.h"
#include "ProductSellWidget.h"
#include "Components/VerticalBox.h"
#include "MainBoardWidget.h"


UMainBoardWidget::UMainBoardWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer) // 부모 클래스 초기화
{

}

void UMainBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();

    GameMode = Cast<ASuperGameMode>(GetWorld()->GetAuthGameMode());
    if (!GameMode)return;
    SetInfoWidget(GameMode->Product);
    purchaseButton->OnClicked.AddDynamic(this, &UMainBoardWidget::OnButtonClicked);
    FVector SpawnLocation(20.0f, 400.0f, 60.0f);
    FTransform SpawnTransform(SpawnLocation);
    productBox = GetWorld()->SpawnActor<AProductBoxSpawner>(ProductBoxSpawner, SpawnTransform);
}
void UMainBoardWidget::OnButtonClicked()
{
    if (selectArrayProduct.Num()<=0)return;

    for (auto product : selectArrayProduct) {
        if (selectArrayProduct.Num() <= 0)return;

        SpawnProductBox(product);
    }
    selectArrayProduct.Empty();
    ProductVerticalBox->ClearChildren();
}

void UMainBoardWidget::SetInfoWidget(TMap<FString, FProductData*> Product)
{
    for (int i = 0; i < Product.Num(); i++) {
        ProductInfoWidget = CreateWidget<UProductInfoWidget>(this, ProductInfoWidgetTool);
        ProductInfoWidget->SetMainBoardReference(this);
        if (GameMode)
        {
            FProductData* Data= GameMode->GetProductDataByIndex(i);

            ProductInfoWidget->ProductName->SetText(FText::FromString(Data->ProductName));
            ProductInfoWidget->StorageStock->SetText(FText::AsNumber(Data->ShelfStock));
            ProductInfoWidget->BoxStock->SetText(FText::AsNumber(Data->StorageStock));
            ProductInfoWidget->ShelfStock->SetText(FText::AsNumber(Data->OrderStock));
            ProductInfoWidget->CostPrice->SetText(FText::Format(NSLOCTEXT("UI", "CostPriceFormat", "개당가격: {0}원"), Data->CostPrice));
            ProductInfoWidget->CostPriceSum->SetText(FText::Format(NSLOCTEXT("UI", "CostPriceSum", "{0}원"), Data->CostPrice*Data->BoxStock));
            ProductInfoWidget->ProductCount->SetText(FText::Format(NSLOCTEXT("UI", "CostPriceFormat", "x{0}"), Data->BoxStock));
            WrapBox->AddChildToWrapBox(ProductInfoWidget);
        }
    }
}
void UMainBoardWidget::SpawnProductBox(FText product)
{
    if (!GameMode)return;
    if (product.IsEmpty())return;

    //FName name = FName(GameMode->Product[product.ToString()]->ProductName);

    FProductData* Data = GameMode->GetProductData(product.ToString());
    if(Data&& GameMode){
        if (productBox) {
            productBox->SpawnBoxHandler(FName(Data->ProductName), FName(Data->ImagePath), Data->CostPrice, Data->BoxStock);
        }
    }
}

void UMainBoardWidget::SetVerticalBox(FText ProductName, FText ProductCount, FText CostPriceSum)
{
    ProductSellWidget = CreateWidget<UProductSellWidget>(this, SellWidgettool);
    ProductSellWidget->ProductName->SetText(ProductName);
    ProductSellWidget->ProductCount->SetText(ProductCount);
    ProductSellWidget->CostPriceSum->SetText(CostPriceSum);
    selectArrayProduct.Add(ProductName);
    ProductVerticalBox->AddChildToVerticalBox(ProductSellWidget);
}