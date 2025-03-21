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
	ProductInfoWidget = CreateWidget<UProductInfoWidget>(this, ProductInfoWidgetTool);

}

void UMainBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();

    GameMode = Cast<ASuperGameMode>(GetWorld()->GetAuthGameMode());
    if (!GameMode)return;
    purchaseButton->OnClicked.AddDynamic(this, &UMainBoardWidget::OnButtonClicked);
    if (!ProductInfoWidgetTool)
    {
        UE_LOG(LogTemp, Error, TEXT("ProductInfoWidgetTool is null!"));
        return;
    }
    for(int i=0;i<4;i++){
    ProductInfoWidget = CreateWidget<UProductInfoWidget>(this, ProductInfoWidgetTool);
    if (!ProductInfoWidget)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create ProductInfoWidget!"));
        return;
    }

    if (!WrapBox)
    {
        UE_LOG(LogTemp, Error, TEXT("WrapBox is nullptr!"));

        return;
    }
    ProductInfoWidget->ProductName->SetText(FText::FromString(FString::Printf(TEXT("TEXT:  %d"), i)));
    WrapBox->AddChildToWrapBox(ProductInfoWidget);
    }
    FVector SpawnLocation(20.0f, 400.0f, 60.0f);
    FTransform SpawnTransform(SpawnLocation);
    FName name = FName(GameMode->Product["Coke"]->ProductName);

    GetWorld()->SpawnActor<AProductBoxSpawner>(ProductBoxSpawner, SpawnTransform)->
    SpawnBoxHandler(name, TEXT("abcdeasdasd"), 200, 200);
}
void UMainBoardWidget::OnButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("asdasdasd"));
}

