#include "CLineTraceZone.h"
#include "Components/BoxComponent.h"

ACLineTraceZone::ACLineTraceZone()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionProfileName(TEXT("LineTraceZone"));
	BoxComponent->SetupAttachment(RootComponent);
}

void ACLineTraceZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACLineTraceZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

