// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMoveToCounterTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"

UAIMoveToCounterTaskNode::UAIMoveToCounterTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UAIMoveToCounterTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UAIMoveToCounterTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UE_LOG(LogTemp, Warning, TEXT("%d"), BlackboardComp->GetValueAsBool(TEXT("IsPurchase")));
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	//if (BlackboardComp->GetValueAsBool(TEXT("IsPurchase"))) {
	//	UE_LOG(LogTemp, Warning,TEXT("Succeeded"))
	//		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	//}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("Failed"));
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	//}


}

EBTNodeResult::Type UAIMoveToCounterTaskNode::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);
	return EBTNodeResult::Aborted;

}
