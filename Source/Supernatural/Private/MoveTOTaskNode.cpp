// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveTOTaskNode.h"
#include "SuperAIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "SuperGameMode.h"
#include "AiCharacter.h"
#include "Kismet/GameplayStatics.h"

UMoveTOTaskNode::UMoveTOTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UMoveTOTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ASuperAIController* AiController = Cast<ASuperAIController>(OwnerComp.GetOwner());
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Counter"), FoundActors);
	Actor = FoundActors[0];
	return EBTNodeResult::InProgress;

}

void UMoveTOTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ASuperAIController* AiController = Cast<ASuperAIController>(OwnerComp.GetOwner());
	AAiCharacter* AI = Cast<AAiCharacter>(AiController->GetCharacter());
	if (AI->isBegin) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		AI->isBegin = false;
		return;
	}
	AiController->MoveToActor(Actor, 0);
}
