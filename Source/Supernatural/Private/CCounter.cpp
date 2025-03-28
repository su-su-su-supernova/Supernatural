#include "CCounter.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Components/WidgetComponent.h"

ACCounter::ACCounter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Counter Body
	CounterBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CounterBody"));
	CounterBody->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tmpBody(TEXT("/Script/Engine.StaticMesh'/Game/MMSupermarket/Equipment/Mesh/SM_CashRegister.SM_CashRegister'"));
	if(tmpBody.Succeeded()) BodyMesh = tmpBody.Object;
	CounterBody->SetStaticMesh(BodyMesh);

	// Counter Monitor
	CounterMonitor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CounterMonitor"));
	CounterMonitor->SetupAttachment(CounterBody);
	CounterMonitor->SetRelativeLocation(FVector(0.000000, -11.089033, 88.137596));
	CounterMonitor->SetRelativeScale3D(FVector(2.170968, 0.05, 1.310078));

	ConstructorHelpers::FObjectFinder<UStaticMesh> tmpMonitor(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (tmpMonitor.Succeeded()) MonitorMesh = tmpMonitor.Object;
	CounterMonitor->SetStaticMesh(MonitorMesh);

	ConstructorHelpers::FObjectFinder<UMaterial> tmpMat(TEXT("/Script/Engine.Material'/Game/Materials/M_CounterMoniter.M_CounterMoniter'"));
	if (tmpMat.Succeeded()) MonitorMat = tmpMat.Object;
	CounterMonitor->SetMaterial(0, MonitorMat);

	// Widget
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(CounterBody);

	// Casher
	CasherBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasherBody"));
	CasherBody->SetupAttachment(CounterBody);
	CasherBody->SetRelativeLocation(FVector(-5.417562, 19.115733, -97.164808));
	CasherBody->SetRelativeRotation(FRotator(0, 90, 0));
	CasherBody->SetRelativeScale3D(FVector(1.000000, 1.537776, 1.000000));

	ConstructorHelpers::FObjectFinder<UStaticMesh> tmpCasher(TEXT("/Script/Engine.StaticMesh'/Game/MMSupermarket/Equipment/Mesh/SM_CheckoutCounter_01.SM_CheckoutCounter_01'"));
	if (tmpCasher.Succeeded()) CasherMesh = tmpCasher.Object;
	CasherBody->SetStaticMesh(CasherMesh);
}

void ACCounter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACCounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

