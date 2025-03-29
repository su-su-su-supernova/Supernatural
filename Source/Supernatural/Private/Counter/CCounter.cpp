#include "CCounter.h"
#include "Components/WidgetComponent.h"
#include "CLineTraceZone.h"
#include "Components/BoxComponent.h"
#include "ProductSalesStandDataAsset.h"
#include "AiCharacter.h"

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

	// Credit Card
	CreditCard = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CreditCard"));
	CreditCard->SetupAttachment(CounterBody);

	CreditCard->SetRelativeLocation(FVector(-73.868370, 15.510121, -11.439597));
	CreditCard->SetRelativeRotation(FRotator(-5.447370, -1.778796, -66.400598));
	CreditCard->SetRelativeScale3D(FVector(3.428577, 3.806632, 3.214357));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpCard(TEXT("/Script/Engine.SkeletalMesh'/Game/DYL/Assets/cc0-magnet-card/source/MagnetCard1.MagnetCard1'"));
	if(tmpCard.Succeeded()) CreditCard->SetSkeletalMesh(tmpCard.Object);

	// AI Spawn Point
	AISpawnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("AISpawnPoint"));
	AISpawnPoint->SetupAttachment(CounterBody);

	AISpawnPoint->SetRelativeLocation(FVector(125.000000, -80.000000, -29.000000));
	AISpawnPoint->SetRelativeRotation(FRotator(0.000000, 90.000000, 0.000000));
	AISpawnPoint->SetRelativeScale3D(FVector(1.500000, 1.500000, 1.000000));

	AISpawnPoint->SetCollisionProfileName(FName("Counter"));
	AISpawnPoint->OnComponentBeginOverlap.AddDynamic(this, &ACCounter::OnAIBeginOverlap);


	// Product Sales Stand Data Asset
	ConstructorHelpers::FObjectFinder<UProductSalesStandDataAsset> tmpProductDA(TEXT("/Script/Supernatural.ProductSalesStandDataAsset'/Game/HWL/Data/NewDataAsset.NewDataAsset'"));
	if(tmpProductDA.Succeeded()) 
	{
		ProductSalesStandDataAsset = tmpProductDA.Object;
		CachedProducts = ProductSalesStandDataAsset->ProdctSalesStandDataTable;
	}

	// Products
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			FString name = FString::Printf(TEXT("CounterProduct_%d"), (i * 2 + j));
			UStaticMeshComponent* tmpMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*name));
			tmpMesh->SetRelativeLocation(FVector(-143.762936, 17.369481, 8.924103) + FVector(0, 39.866659, 0) * i + FVector(37.594206, 0, 0) * j);
			tmpMesh->SetupAttachment(CounterBody);
			tmpMesh->SetVisibility(false);
			Products.Add(tmpMesh);
		}
	}
}

void ACCounter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACCounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ACCounter::OnAIBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	class AAiCharacter* customer = Cast<AAiCharacter>(OtherActor);

	if (customer)
	{
		// customer의 구매 목록을 가져온다
		ShoppingList = {EProductDivide::Snack1, EProductDivide::Snack2, EProductDivide::Snack1};

		// customer가 구매한 총 물품 개수를 파악한다
		NPurchasedItems = ShoppingList.Num();

		// 구매 목록에 있는 순서대로 product를 카운터에 올려둔다
		for (int32 i = 0; i < NPurchasedItems; i++)
		{
			Products[i]->SetStaticMesh(CachedProducts[ShoppingList[i]].Snack1);
			Products[i]->ComponentTags.Add(FName("Product"));
		}

		// 구매한 상품들이 카운터에 다 진열되었음을 명시한다
		bIsProductsOnCounter = true;
		bCanCalculate = true;

		// Player가 물품 계산을 위해 카운터 위에 있는 제품들을 클릭한다
		NCountedItems = 0;
		TotalCost = 0;
		InputCost = 0;

	}
}



