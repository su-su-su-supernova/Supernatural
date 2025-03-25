// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMoveToTaskNode.h"

UAIMoveToTaskNode::UAIMoveToTaskNode()
{

}
// �½�ũ�� ���۵� �� ȣ��Ǹ�, �ֿ� ������ �����ϰ� ����� ��ȯ�մϴ�.
// - OwnerComp: �����̺�� Ʈ�� ������Ʈ�� ���� (������, AI ��Ʈ�ѷ� ��).
// - NodeMemory: �½�ũ�� �޸� ������ (���� �����).
// - ��ȯ��: Succeeded(����), Failed(����), InProgress(���� ��).
EBTNodeResult::Type UAIMoveToTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("testtq1"));
	return EBTNodeResult::Succeeded; // �½�ũ�� ������ �ʰ� ƽ�� ��ٸ�
}
// �½�ũ�� "���� ��" ������ �� �� ������ ȣ��Ǿ� ������Ʈ ������ ó���մϴ�.
// - OwnerComp: �����̺�� Ʈ�� ������Ʈ.
// - NodeMemory: �½�ũ ���� ����� �޸�.
// - DeltaSeconds: ������ �� �ð� ���� (float).
void UAIMoveToTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}
// �½�ũ�� �ߴ�(abort)�� �� ȣ��Ǿ� ���� �۾��� �����մϴ�.
// - OwnerComp: �����̺�� Ʈ�� ������Ʈ.
// - NodeMemory: �½�ũ ���� ����� �޸�.
// - ��ȯ��: �ߴ� �� ��� (���� Succeeded�� Failed).
EBTNodeResult::Type UAIMoveToTaskNode::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}
