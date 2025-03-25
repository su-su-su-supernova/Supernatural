// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIMoveToTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class SUPERNATURAL_API UAIMoveToTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

    UAIMoveToTaskNode();

public:
    // �½�ũ�� ���۵� �� ȣ��Ǹ�, �ֿ� ������ �����ϰ� ����� ��ȯ�մϴ�.
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    // �½�ũ�� "���� ��" ������ �� �� ������ ȣ��Ǿ� ������Ʈ ������ ó���մϴ�.
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

    // �½�ũ�� �ߴ�(abort)�� �� ȣ��Ǿ� ���� �۾��� �����մϴ�.
    virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
