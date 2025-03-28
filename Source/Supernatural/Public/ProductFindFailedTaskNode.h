// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ProductFindFailedTaskNode.generated.h"

/**
 *
 */
UCLASS()
class SUPERNATURAL_API UProductFindFailedTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
    UProductFindFailedTaskNode();
public:
    // �½�ũ�� ���۵� �� ȣ��Ǹ�, �ֿ� ������ �����ϰ� ����� ��ȯ�մϴ�.
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    // �½�ũ�� "���� ��" ������ �� �� ������ ȣ��Ǿ� ������Ʈ ������ ó���մϴ�.
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

    // �½�ũ�� �ߴ�(abort)�� �� ȣ��Ǿ� ���� �۾��� �����մϴ�.
    virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


public:
    FVector getRandomLocation();
    FVector TargetLocation;
    float CurrentTime = 0.0f;
    TArray<AActor*> FoundActors;

};
