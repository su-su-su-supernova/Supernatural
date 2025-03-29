// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EndPosMoveTaskNode.generated.h"

/**
 *
 */
UCLASS()
class SUPERNATURAL_API UEndPosMoveTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UEndPosMoveTaskNode();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	class AActor* Actor;

};
