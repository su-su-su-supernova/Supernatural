// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveTOTaskNode.h"
#include "SuperAIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "SuperGameMode.h"
#include "AiCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "CCounter.h"
#include "EngineUtils.h"
#include "Components/BoxComponent.h"

UMoveTOTaskNode::UMoveTOTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UMoveTOTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ASuperAIController* AiController = Cast<ASuperAIController>(OwnerComp.GetOwner());
	TArray<USceneComponent*> FoundComponents;
	for (TActorIterator<ACCounter> It(GetWorld()); It; ++It)
	{
		ACCounter* Counter = *It;
		if (!Counter || !Counter->AISpawnPoint) continue;
		if (Counter->AISpawnPoint->ComponentHasTag("Counter"))
		{
			FoundComponents.Add(Counter->AISpawnPoint);
			break;
		}
	}
	UE_LOG(LogTemp, Log, TEXT("%f"), FoundComponents[0]->GetComponentLocation().Size());

	if (FoundComponents.Num() > 0) {
		ComponentVector = FoundComponents[0]->GetComponentLocation();
	}
	return EBTNodeResult::InProgress;

}

void UMoveTOTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ASuperAIController* AiController = Cast<ASuperAIController>(OwnerComp.GetOwner());
	//AAiCharacter* AI = Cast<AAiCharacter>(AiController->GetCharacter());
	//if (AiController->TicketNumber == -1) {
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	//}
	//if (AI->isBegin) {
	//	AI->isBegin = false;
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//	return;
	//}
	AiController->MoveToLocation(ComponentVector);
}
