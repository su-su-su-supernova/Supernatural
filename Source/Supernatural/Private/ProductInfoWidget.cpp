// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductInfoWidget.h"
#include "Components/Button.h"
#include "MainBoardWidget.h"
#include "Components/TextBlock.h"


void UProductInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	AddBTN->OnClicked.AddDynamic(this, &UProductInfoWidget::OnButtonClicked);


}

void UProductInfoWidget::OnButtonClicked()
{
    if (!IsValid(MainBoardRef))
    {
        return;
    }
    MainBoardRef->SetVerticalBox(ProductName->GetText(),ProductCount->GetText(),CostPriceSum->GetText());
}

void UProductInfoWidget::SetMainBoardReference(UMainBoardWidget* InMainBoard)
{
	MainBoardRef = InMainBoard;
}

//void UProductInfoWidget::SetMainBoardReference(UMainBoardWidget* InMainBoard)
//{
//
//}
