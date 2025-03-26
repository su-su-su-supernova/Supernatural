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
// �½�ũ�� ���۵� �� ȣ��Ǹ�, �ֿ� ������ �����ϰ� ����� ��ȯ�մϴ�.
// - OwnerComp: �����̺�� Ʈ�� ������Ʈ�� ���� (������, AI ��Ʈ�ѷ� ��).
// - NodeMemory: �½�ũ�� �޸� ������ (���� �����).
// - ��ȯ��: Succeeded(����), Failed(����), InProgress(���� ��).
EBTNodeResult::Type UAIMoveToTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BlackboardComp = OwnerComp.GetBlackboardComponent();
	UObject* PlayerObject = BlackboardComp->GetValueAsObject(TEXT("PlayerClass"));
	UObject* ProductObject = BlackboardComp->GetValueAsObject(TEXT("ProductClass"));
	PlayerPawn = Cast<APawn>(PlayerObject);
	ProductActor = Cast<AActor>(ProductObject);
	AiController = Cast<ASuperAIController>(OwnerComp.GetAIOwner());
	PlayerPawn->bUseControllerRotationYaw = false;
	//UE_LOG(LogTemp, Warning, TEXT(">>>%s"),ProductActor->GetActorLocation().ToString());

	return EBTNodeResult::InProgress;
}
// �½�ũ�� "���� ��" ������ �� �� ������ ȣ��Ǿ� ������Ʈ ������ ó���մϴ�.
// - OwnerComp: �����̺�� Ʈ�� ������Ʈ.
// - NodeMemory: �½�ũ ���� ����� �޸�.
// - DeltaSeconds: ������ �� �ð� ���� (float).
void UAIMoveToTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!AiController || !PlayerPawn)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}

	FindActor();

	// �̵� ���� üũ
	if (AiController->GetMoveStatus() == EPathFollowingStatus::Idle)
	{
		BlackboardComp = OwnerComp.GetBlackboardComponent();
		UE_LOG(LogTemp, Warning, TEXT("next1"));
		BlackboardComp->SetValueAsBool(TEXT("IsSelling"), true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
// �½�ũ�� �ߴ�(abort)�� �� ȣ��Ǿ� ���� �۾��� �����մϴ�.
// - OwnerComp: �����̺�� Ʈ�� ������Ʈ.
// - NodeMemory: �½�ũ ���� ����� �޸�.
// - ��ȯ��: �ߴ� �� ��� (���� Succeeded�� Failed).
EBTNodeResult::Type UAIMoveToTaskNode::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Aborted;
}

void UAIMoveToTaskNode::FindActor()
{
	if (!AiController)return;
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
