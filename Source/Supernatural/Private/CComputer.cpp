#include "CComputer.h"
#include "Components/WidgetComponent.h"
#include "SuperGameMode.h"

ACComputer::ACComputer()
{
	PrimaryActorTick.bCanEverTick = true;

	//BaseComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BaseComp"));
	//SetRootComponent(BaseComponent);
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetDrawSize(FVector2D(600, 300));
	WidgetComponent->SetDrawAtDesiredSize(true);
	WidgetComponent->SetRelativeScale3D(FVector(0.2));
	WidgetComponent->SetupAttachment(BaseComponent);
	//UMainBoardWidget* WidgetInstance = CreateWidget<UMainBoardWidget>(GetWorld(), MainWidget);
	//if (WidgetInstance) {
	//	WidgetComponent->SetWidget(WidgetInstance);
	//}
}

void ACComputer::BeginPlay()
{
	Super::BeginPlay();

	auto GameMode = Cast<ASuperGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode)return;
	UE_LOG(LogTemp, Log, TEXT("%d"), GameMode->Product["Coke"]->CostPrice);
}

void ACComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



