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
	//WidgetComponent->GetWidget()

	// Casher
	CasherBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasherBody"));
	CasherBody->SetupAttachment(CounterBody);
	CasherBody->SetRelativeLocation(FVector(-5.417562, 19.115733, -97.164808));
	CasherBody->SetRelativeRotation(FRotator(0, 90, 0));
	CasherBody->SetRelativeScale3D(FVector(1.000000, 1.537776, 1.000000));

	ConstructorHelpers::FObjectFinder<UStaticMesh> tmpCasher(TEXT("/Script/Engine.StaticMesh'/Game/MMSupermarket/Equipment/Mesh/SM_CheckoutCounter_01.SM_CheckoutCounter_01'"));
	if (tmpCasher.Succeeded()) CasherMesh = tmpCasher.Object;
	CasherBody->SetStaticMesh(CasherMesh);

	// Magnetic Card
	MagneticCard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MagneticCard"));
	MagneticCard->SetupAttachment(CounterBody);
	MagneticCard->SetRelativeLocation(FVector(-56.585265, 6.646232, 2.207688));
	MagneticCard->SetRelativeRotation(FRotator(0, -30, -90));
	MagneticCard->SetRelativeScale3D(FVector(0.32));

	ConstructorHelpers::FObjectFinder<UStaticMesh> tmpCard(TEXT("/Script/Engine.StaticMesh'/Game/DYL/Meshes/Bank_Card_3D_Model/uploads_files_2492273_Card.uploads_files_2492273_Card'"));
	if(tmpCard.Succeeded()) MagneticCardMesh = tmpCard.Object;
	MagneticCard->SetStaticMesh(MagneticCardMesh);
	MagneticCard->ComponentTags.Add("Card");
	MagneticCard->SetVisibility(false);

	// AI Spawn Point
	AISpawnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("AISpawnPoint"));
	AISpawnPoint->SetupAttachment(CounterBody);

	AISpawnPoint->SetRelativeLocation(FVector(125.000000, -80.000000, -29.000000));
	AISpawnPoint->SetRelativeRotation(FRotator(0.000000, 90.000000, 0.000000));
	AISpawnPoint->SetRelativeScale3D(FVector(1.500000, 1.500000, 1.000000));

	AISpawnPoint->SetCollisionProfileName(FName("Counter"));
	AISpawnPoint->OnComponentBeginOverlap.AddDynamic(this, &ACCounter::OnAIBeginOverlap);


	// Product Sales Stand Data Asset
	ConstructorHelpers::FObjectFinder<UProductSalesStandDataAsset> tmpProductDA(TEXT("/Script/Supernatural.ProductSalesStandDataAsset'/Game/HWL/Data/DA_Mesh.DA_Mesh'"));
	if(tmpProductDA.Succeeded())
	{
		ProductSalesStandDataAsset = tmpProductDA.Object;
		CachedProducts = ProductSalesStandDataAsset->ProdctSalesStandDataTable;
		//UE_LOG(LogTemp, Error, TEXT(">>>>>>>>> Load Product DA SUCCESS <<<<<<<<<<"));
	}

	// Products
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			FString name = FString::Printf(TEXT("CounterProduct%d"), (i * 2 + j + 1));
			UStaticMeshComponent* tmpMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*name));

			//UE_LOG(LogTemp, Warning, TEXT("[tmpMesh %d Name] : %s"), i * 2 + j, *(tmpMesh->GetName()));
			tmpMesh->SetupAttachment(CounterBody);
			tmpMesh->SetRelativeLocation(FVector(-143.762936, 17.369481, 1) + FVector(0, 39.866659, 0) * i + FVector(37.594206, 0, 0) * j);
			//UE_LOG(LogTemp, Warning, TEXT("[tmpMesh %d Location] : %s"), i*2+j, *tmpMesh->GetRelativeLocation().ToString());
			tmpMesh->SetVisibility(false);
			Products.Add(tmpMesh);
		}
	}

	//for (auto p : Products)
	//	UE_LOG(LogTemp, Warning, TEXT(">>> %s <<<"), *(p->GetName()))
}

void ACCounter::BeginPlay()
{
	Super::BeginPlay();
  
	CustomerArrived();
}


void ACCounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 상품을 카운터에 올려두기
	PlaceProductsOnCounter(DeltaTime);

	// 카드 지불하기
	PayWithCreditCard(DeltaTime);
}



void ACCounter::OnAIBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	class AAiCharacter* customer = Cast<AAiCharacter>(OtherActor);

	if (customer)
	{
		CustomerArrived();
	}
}

void ACCounter::CustomerArrived()
{
	// 계산에 사용할 데이터들을 초기화해준다
	bIsCustomerArrived = true;
	NCountedItems = 0;
	TotalCost = 0;
	InputCost = 0;

	// customer의 구매 목록을 가져온다
	// 여기 수정해줘야 함
	ShoppingList = { EProductType::CAKE, EProductType::COKE, EProductType::TEA };

	// customer가 구매한 총 물품 개수를 파악한다
	NPurchasedItems = ShoppingList.Num();

	// 구매 목록에 있는 순서대로 product를 카운터에 올려둔다
	for (int32 i = 0; i < NPurchasedItems; i++)
	{
		if (Products[i] == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("<<<<< Products[i] is EMPTY >>>>>"));
			return;
		}
		if (CachedProducts.Num() == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("<<<<< CachedProducts is EMPTY >>>>>"));
			return;
		}
			
		Products[i]->SetStaticMesh(CachedProducts[ShoppingList[i]].MeshData);
		Products[i]->SetVisibility(false);
		Products[i]->ComponentTags.Add(FName("Product"));
	}

	// Static Mesh Component의 visibility를 켜준다
	MaxVisibilityOn = NPurchasedItems;
	bCanVisibilityOn = true;
}

void ACCounter::PlaceProductsOnCounter(float InDeltaTime)
{
	if (bCanVisibilityOn)
		CurVisibilityTime += InDeltaTime;

	// 시간이 되면
	if (CurVisibilityTime >= MaxVisibilityTime)
	{
		// UE_LOG(LogTemp, Warning, TEXT("[CCounter] Current Time : %f / CurVisibilityOn : %d"), CurVisibilityTime, CurVisibilityOn);
		Products[CurVisibilityOn]->SetVisibility(true);
		CurVisibilityTime = 0;
		CurVisibilityOn++;

		// 상품을 전부 진열하면
		if (CurVisibilityOn == MaxVisibilityOn)
		{
			CurVisibilityOn = 0;
			bCanVisibilityOn = false;

			// 구매한 상품들이 카운터에 다 진열되었음을 명시한다
			bAreProductsOnCounter = true;

			// Player가 계산할 수 있음을 명시한다
			bCanCalculate = true;

			// UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> All Products On COUNTER / %d"), bCanCalculate);
		}
	}
}

void ACCounter::PayWithCreditCard(float InDeltaTime)
{
	// customer가 card를 지불하지 않았다면
	if (bIsScanningBarcodeComplete && !bDidCustomerGiveCard)
	{
		CurPayTime += InDeltaTime;

		if (CurPayTime >= MaxPayTime)
		{
			// UE_LOG(LogTemp, Warning, TEXT(">>> Pay With Credit Card Please"));
			if (MagneticCard == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("<<< Credit Card is EMPTY >>>"));
				return;
			}
			MagneticCard->SetVisibility(true);
			CurPayTime = 0;

			// UE_LOG(LogTemp, Warning, TEXT(">>> Get Credit Card from Customer"));
			bDidCustomerGiveCard = true;
		}
	}

}

void ACCounter::GrabCard()
{
	// 카드의 Visibility를 켜준다
	MagneticCard->SetVisibility(false);

	// 계산할 수 있는 상태임을 명시해준다
	bCanCalculate = true;
}

void ACCounter::CalculateStart()
{
}





