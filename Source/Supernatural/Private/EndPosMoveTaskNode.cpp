// Fill out your copyright notice in the Description page of Project Settings.


#include "EndPosMoveTaskNode.h"
#include "SuperAIController.h"
#include "Kismet/GameplayStatics.h"
#include "AiCharacter.h"

UEndPosMoveTaskNode::UEndPosMoveTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UEndPosMoveTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ASuperAIController* AiController = Cast<ASuperAIController>(OwnerComp.GetOwner());
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("End"), FoundActors);
	Actor = FoundActors[0];
	return EBTNodeResult::InProgress;
}

void UEndPosMoveTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ASuperAIController* AiController = Cast<ASuperAIController>(OwnerComp.GetOwner());
	AAiCharacter* AI = Cast<AAiCharacter>(AiController->GetCharacter());

	if (AI->isBegin) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);
		AI->isBegin = false;
		return;
	}

	AiController->MoveToActor(Actor, 0);

}
