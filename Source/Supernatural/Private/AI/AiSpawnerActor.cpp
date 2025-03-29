// Fill out your copyright notice in the Description page of Project Settings.


#include "AiSpawnerActor.h"
#include "Components/ArrowComponent.h"
#include "AiCharacter.h"
#include "SuperAIController.h"

// Sets default values
AAiSpawnerActor::AAiSpawnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	ArrowComp->SetRelativeRotation(FRotator(-90, 180, 0));
	ArrowComp->SetupAttachment(RootComponent);

	ConstructorHelpers::FClassFinder<AAiCharacter>TempAI(TEXT("/Script/Engine.Blueprint'/Game/HWL/BluePrint/BP_AI.BP_AI_C'"));
	if (TempAI.Succeeded()) AiCharacterSample = TempAI.Class;

}

// Called when the game starts or when spawned
void AAiSpawnerActor::BeginPlay()
{
	Super::BeginPlay();
	//for(int i=0;i<5;i++){

	//AiCharacter->SetActorRotation(FRotator(-90,180,0));

	//}

}

// Called every frame
void AAiSpawnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentTime >= 5) {
		AAiCharacter* AiCharacter = GetWorld()->SpawnActorDeferred<AAiCharacter>(AiCharacterSample, ArrowComp->GetComponentTransform());
		if (AiCharacter) {
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(ArrowComp->GetComponentLocation()); // ��ġ�� ������
			SpawnTransform.SetRotation(FQuat::Identity); // ȸ���� �⺻��(0, 0, 0)���� ����
			SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
			AiCharacter->FinishSpawning(SpawnTransform);

			ASuperAIController* AIController = GetWorld()->SpawnActor<ASuperAIController>(ASuperAIController::StaticClass(), SpawnTransform);
			if (AIController)
			{
				AIController->Possess(AiCharacter);
			}
		}
		CurrentTime = 0.0f;
	}
	CurrentTime += DeltaTime;

}

