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
	GetBlackboardComponent()->SetValueAsBool(TEXT("IsPurchase"), false);
	for (int i = 0; i < 4; i++) {
		randomVaule = FMath::RandRange(0, GameMode->Product.Num() - 1);
		ProductName[i]=(GameMode->GetProductDataByIndex(randomVaule)->ProductName);

		//UE_LOG(LogTemp, Warning, TEXT("index : %s"), *ProductName[i]);
	}
	GetBlackboardComponent()->SetValueAsBool(TEXT("IsSelling"), false);

}

void ASuperAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!ProductName) return;
	//SelectNextProduct();
	isBuyProduct[index] = GetBlackboardComponent()->GetValueAsBool(TEXT("IsSelling"));

	BuyCheck();
}

bool ASuperAIController::SelectNextProduct()
{

	if (isBuyProduct[index])
	{
		UE_LOG(LogTemp, Warning, TEXT("Add Index :%d"), index);

		index++;
	}
	if(!(isBuyProduct[index]))
	{
		FName TargetTag = FName(*ProductName[index]);

		TArray<AActor*> FoundActors;

		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TargetTag, FoundActors);

		GetBlackboardComponent()->SetValueAsObject(TEXT("ProductClass"), FoundActors[0]);
		GetBlackboardComponent()->SetValueAsBool(TEXT("IsSelling"), isBuyProduct[index]);

	}
	return true;
}

void ASuperAIController::BuyCheck()
{
	for (int i = 0; i < 4; i++) {
		if (!isBuyProduct[i]) {
			return;
		}
	}

	GetBlackboardComponent()->SetValueAsBool(TEXT("IsPurchase"), true);
}
