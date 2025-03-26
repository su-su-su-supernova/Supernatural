// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIMoveToCounterTaskNode.generated.h"

/**
 *
 */
UCLASS()
class SUPERNATURAL_API UAIMoveToCounterTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

    UAIMoveToCounterTaskNode();
public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

    virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
