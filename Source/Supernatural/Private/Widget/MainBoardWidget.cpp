// Fill out your copyright notice in the Description page of Project Settings.


#include "MainBoardWidget.h"
#include "ProductInfoWidget.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ProductBoxSpawner.h"
#include "SuperGameMode.h"
#include "ProductSellWidget.h"
#include "Components/VerticalBox.h"
#include "Sound/SoundCue.h"
#include "CPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"


UMainBoardWidget::UMainBoardWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer) // 부모 클래스 초기화
{
    ConstructorHelpers::FObjectFinder<USoundCue>SoundCueTool(TEXT("/Script/Engine.SoundCue'/Game/HWL/Sound/Sound_Homeplus_Cue.Sound_Homeplus_Cue'"));
    if (SoundCueTool.Succeeded()) MainBoardSound = SoundCueTool.Object;

    ConstructorHelpers::FObjectFinder<USoundCue>SoundCueTool2(TEXT("/Script/Engine.SoundWave'/Game/DYL/Sounds/Sound_Pay.Sound_Pay'"));
    if (SoundCueTool.Succeeded()) MainBoardSound2 = SoundCueTool2.Object;
}

void UMainBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();

    GameMode = Cast<ASuperGameMode>(GetWorld()->GetAuthGameMode());
    if (!GameMode)return;
    SetInfoWidget(GameMode->Product);
    purchaseButton->OnClicked.AddDynamic(this, &UMainBoardWidget::OnButtonClicked);
    SpawnerBtn->OnClicked.AddDynamic(this, &UMainBoardWidget::OnSpwnerButtonClicked);
    FVector SpawnLocation(774.547301f, -1708.812250f, 79.15f);
    FTransform SpawnTransform(SpawnLocation);
    productBox = GetWorld()->SpawnActor<AProductBoxSpawner>(ProductBoxSpawner, SpawnTransform);
}

void UMainBoardWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
    Super::NativeTick(MyGeometry, DeltaTime);
    FString MoneyText = FString::Printf(TEXT("보유 돈: %d원"), GameMode->GetTotalSales());
    FText MoneyTextFText = FText::FromString(MoneyText);
    Money->SetText(MoneyTextFText);
}

void UMainBoardWidget::OnButtonClicked()
{
    if (selectArrayProduct.Num()<=0)return;

    for (auto product : selectArrayProduct) {
        if (selectArrayProduct.Num() <= 0)return;
        FProductData* Data = GameMode->GetProductData(product);

        GameMode->SetTotalSales(GameMode->GetTotalSales() - Data->CostPrice*Data->BoxStock);

        SpawnProductBox(product);
    }
    ACPlayer* player = Cast<ACPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
    UGameplayStatics::PlaySoundAtLocation(this, MainBoardSound2, player->GetActorLocation());
    selectArrayProduct.Empty();
    ProductVerticalBox->ClearChildren();
}

void UMainBoardWidget::OnSpwnerButtonClicked()
{
    if (!GameMode) return;
    ACPlayer* player = Cast<ACPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
    UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, MainBoardSound, player->GetActorLocation());
    if (GameMode->SpawnAIHander()) {
        if (AudioComponent->IsPlaying()) return;
        AudioComponent->Play();
    }
    else {
        AudioComponent->Stop();
    }
}

void UMainBoardWidget::SetInfoWidget(TMap<EProductType, FProductData*> Product)
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
            ProductInfoWidget->widgetEnum = Data->ProductEnum;
            WrapBox->AddChildToWrapBox(ProductInfoWidget);
        }
    }
}
void UMainBoardWidget::SpawnProductBox(EProductType product)
{
    if (!GameMode)return;


    FProductData* Data = GameMode->GetProductData(product);
    if(Data&& GameMode){
        if (productBox) {
            productBox->SpawnBoxHandler(Data);
        }
    }
}

void UMainBoardWidget::SetVerticalBox(EProductType Enum,FText ProductName, FText ProductCount, FText CostPriceSum)
{
    ProductSellWidget = CreateWidget<UProductSellWidget>(this, SellWidgettool);
    ProductSellWidget->ProductName->SetText(ProductName);
    ProductSellWidget->ProductCount->SetText(ProductCount);
    ProductSellWidget->CostPriceSum->SetText(CostPriceSum);
    selectArrayProduct.Add(Enum);
    ProductVerticalBox->AddChildToVerticalBox(ProductSellWidget);

    FString TextString = CostPriceSum.ToString();
    TextString = TextString.RightChop(1);
    int32 ConvertedInt = FCString::Atoi(*TextString);
    PurchaseCost += ConvertedInt;
}