// Fill out your copyright notice in the Description page of Project Settings.


#include "MainBoardWidget.h"
#include "ProductInfoWidget.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ProductBoxSpawner.h"
#include "SuperGameMode.h"


UMainBoardWidget::UMainBoardWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer) // 부모 클래스 초기화
{
	//ProductInfoWidget = CreateWidget<UProductInfoWidget>(this, ProductInfoWidgetTool);

}

void UMainBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();

    GameMode = Cast<ASuperGameMode>(GetWorld()->GetAuthGameMode());
    if (!GameMode)return;
    SetInfoWidget(GameMode->Product);
    purchaseButton->OnClicked.AddDynamic(this, &UMainBoardWidget::OnButtonClicked);


    SpawnProductBox();


}
void UMainBoardWidget::OnButtonClicked()
{
    //SpawnProductBox();
    UE_LOG(LogTemp,Warning,TEXT("TQ"));
}

void UMainBoardWidget::SetInfoWidget(TMap<FString, FProductData*> Product)
{
    for (int i = 0; i < Product.Num(); i++) {
        ProductInfoWidget = CreateWidget<UProductInfoWidget>(this, ProductInfoWidgetTool);
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

void UMainBoardWidget::SpawnProductBox()
{
    FVector SpawnLocation(20.0f, 400.0f, 60.0f);
    FTransform SpawnTransform(SpawnLocation);
    FName name = FName(GameMode->Product["Coke"]->ProductName);

    FProductData* Data = GameMode->GetProductData("Coke");

    GetWorld()->SpawnActor<AProductBoxSpawner>(ProductBoxSpawner, SpawnTransform)->
        SpawnBoxHandler(FName(Data->ProductName),FName(Data->ImagePath), Data->CostPrice, Data->BoxStock);
}

