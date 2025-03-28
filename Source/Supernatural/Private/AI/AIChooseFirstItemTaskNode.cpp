// Fill out your copyright notice in the Description page of Project Settings.


#include "AIChooseFirstItemTaskNode.h"
#include "SuperGameMode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SuperAIController.h"

UAIChooseFirstItemTaskNode::UAIChooseFirstItemTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UAIChooseFirstItemTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	ASuperAIController* AIPlayerContaroller = Cast<ASuperAIController>(OwnerComp.GetAIOwner());
	if (AIPlayerContaroller->SelectNextProduct()) {
		return EBTNodeResult::Succeeded;
	}
	else {
		return EBTNodeResult::Failed;
	}
}

void UAIChooseFirstItemTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

EBTNodeResult::Type UAIChooseFirstItemTaskNode::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);
	return EBTNodeResult::Aborted;
}
