// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMoveToTaskNode.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "SuperAIController.h"
#include "AiCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
UAIMoveToTaskNode::UAIMoveToTaskNode()
{
	bNotifyTick = true;
}
// 태스크가 시작될 때 호출되며, 주요 로직을 실행하고 결과를 반환합니다.
// - OwnerComp: 비헤이비어 트리 컴포넌트에 접근 (블랙보드, AI 컨트롤러 등).
// - NodeMemory: 태스크별 메모리 데이터 (상태 저장용).
// - 반환값: Succeeded(성공), Failed(실패), InProgress(진행 중).
EBTNodeResult::Type UAIMoveToTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BlackboardComp = OwnerComp.GetBlackboardComponent();
	UObject* ProductObject = BlackboardComp->GetValueAsObject(TEXT("ProductClass"));
	ProductActor = Cast<AActor>(ProductObject);
	AiController = Cast<ASuperAIController>(OwnerComp.GetAIOwner());
	//UE_LOG(LogTemp, Warning, TEXT(">>>%s"),ProductActor->GetActorLocation().ToString());

	return EBTNodeResult::InProgress;
}
// 태스크가 "진행 중" 상태일 때 매 프레임 호출되어 업데이트 로직을 처리합니다.
// - OwnerComp: 비헤이비어 트리 컴포넌트.
// - NodeMemory: 태스크 상태 저장용 메모리.
// - DeltaSeconds: 프레임 간 시간 간격 (float).
void UAIMoveToTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ASuperAIController* PC = Cast<ASuperAIController>(OwnerComp.GetOwner());

	FindActor();
	AAiCharacter* ai = Cast<AAiCharacter>(PC->GetCharacter());
	// 이동 상태 체크
	if (ai->isBegin)
	{
		BlackboardComp = OwnerComp.GetBlackboardComponent();
		BlackboardComp->SetValueAsBool(TEXT("IsSelling"), true);
		ai->isBegin = false; PC->AddIndex();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
// 태스크가 중단(abort)될 때 호출되어 정리 작업을 수행합니다.
// - OwnerComp: 비헤이비어 트리 컴포넌트.
// - NodeMemory: 태스크 상태 저장용 메모리.
// - 반환값: 중단 후 결과 (보통 Succeeded나 Failed).
EBTNodeResult::Type UAIMoveToTaskNode::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Aborted;
}

void UAIMoveToTaskNode::FindActor()
{
	if (AiController->LineOfSightTo(ProductActor)) {
		AiController->SetFocus(ProductActor);
		AiController->GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = true;
	}
	else {
		AiController->ClearFocus(EAIFocusPriority::Gameplay);
		AiController->GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	AiController->MoveToActor(ProductActor, 0);
}
