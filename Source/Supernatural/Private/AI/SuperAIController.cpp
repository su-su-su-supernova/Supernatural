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
	TArray<int32> AvailableIndices;
	for (int32 i = 0; i < GameMode->Product.Num(); i++) {
		AvailableIndices.Add(i);
	}

	// �迭 ũ�Ⱑ 4�� �����Ǿ� �����Ƿ�, �ִ� 4���� ����
	for (int i = 0; i < 4 && AvailableIndices.Num() > 0; i++) {
		int32 RandomIndex = FMath::RandRange(0, AvailableIndices.Num() - 1); // ���� �ε��� �� �ϳ� ����
		int32 SelectedIndex = AvailableIndices[RandomIndex]; // ���õ� �ε���
		ProductName[i] = GameMode->GetProductDataByIndex(SelectedIndex)->ProductName; // ��ǰ �̸� �Ҵ�
		AvailableIndices.RemoveAt(RandomIndex); // ����� �ε��� ���� (�ߺ� ����)

		UE_LOG(LogTemp, Warning, TEXT("index : %s"), *ProductName[i]);
	}
}

void ASuperAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!ProductName) return;

}

bool ASuperAIController::SelectNextProduct()
{
	if (index >= 4)return false;
	FName TargetTag = FName(*ProductName[index]);
	CurrentName = ProductName[index];
	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TargetTag, FoundActors);

	GetBlackboardComponent()->SetValueAsObject(TEXT("ProductClass"), FoundActors[0]);
	GetBlackboardComponent()->SetValueAsBool(TEXT("IsSelling"), isBuyProduct[index]);
	return true;
}

void ASuperAIController::AddIndex()
{
	index++;
}
