// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveTOTaskNode.generated.h"

/**
 *UE_LOG(LogTemp,Log,TEXT("TEST"));
 */
UCLASS()
class SUPERNATURAL_API UMoveTOTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMoveTOTaskNode();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	class AActor* Actor;
};
