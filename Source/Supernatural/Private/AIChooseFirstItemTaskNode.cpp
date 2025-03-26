// Fill out your copyright notice in the Description page of Project Settings.


#include "AIChooseFirstItemTaskNode.h"
#include "SuperGameMode.h"
#include "BehaviorTree/BlackboardComponent.h"

UAIChooseFirstItemTaskNode::UAIChooseFirstItemTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UAIChooseFirstItemTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();


	return EBTNodeResult::Succeeded;

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
