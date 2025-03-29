// Fill out your copyright notice in the Description page of Project Settings.


#include "AIServiceNode.h"
#include "SuperAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UAIServiceNode::UAIServiceNode()
{

}

void UAIServiceNode::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	ASuperAIController* AIPC = Cast<ASuperAIController>(OwnerComp.GetOwner());
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("AIState"), (uint8)AIPC->AIState);
	//OwnerComp.GetBlackboardComponent()->SetValueAsInt(TEXT("Index"), AIPC->index);
}
