// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperAIController.h"
#include "Kismet/GameplayStatics.h"
#include "AiCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SuperGameMode.h"
#include "CPlayer.h"

ASuperAIController::ASuperAIController()
{

	ConstructorHelpers::FObjectFinder<UBehaviorTree> AIBehavior(TEXT("/Game/HWL/AI/BT_AI.BT_AI"));
	if (AIBehavior.Succeeded())AIBehaviorTree = AIBehavior.Object;


}

void ASuperAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(AIBehaviorTree);

	GameMode = Cast<ASuperGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode)return;
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ACPlayer* player = Cast<ACPlayer>(PlayerPawn);
	GetBlackboardComponent()->SetValueAsObject(TEXT("PlayerClass"), player);
	for (int i = 0; i < 4; i++) {1
		randomVaule = FMath::RandRange(0, GameMode->Product.Num() - 1);
		ProductName[i]=(GameMode->GetProductDataByIndex(randomVaule)->ProductName);
	}
	TArray<AActor*> FoundActors;

	FName TargetTag = FName(*ProductName[index]);

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TargetTag, FoundActors);
	if (FoundActors[0] == nullptr)return;
	GetBlackboardComponent()->SetValueAsObject(TEXT("ProductClass"), FoundActors[0]);
	//SelectNextProduct();



	//GetBlackboardComponent()->SetValueAsBool(TEXT("isBuyProduct"), isBuyProduct[index]);



}

void ASuperAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!ProductName) return;
	//SelectNextProduct();

}

void ASuperAIController::SelectNextProduct()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (GetBlackboardComponent()->GetValueAsBool(TEXT("isBuyProduct"))) {
		index++;
	}

	TArray<AActor*> FoundActors;

	FName TargetTag = FName(*ProductName[index]);

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TargetTag, FoundActors);
	if (FoundActors[0]==nullptr)return;
	GetBlackboardComponent()->SetValueAsObject(TEXT("PlayerClass"), PlayerPawn);
	GetBlackboardComponent()->SetValueAsObject(TEXT("ProductClass"), FoundActors[0]);
	//GetBlackboardComponent()->SetValueAsBool(TEXT("isBuyProduct"), isBuyProduct[index]);
	//UE_LOG(LogTemp, Warning, TEXT(">>>%s"), *FoundActors[0]->GetActorLocation().ToString());
}
