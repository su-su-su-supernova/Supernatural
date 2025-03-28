// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AIServiceNode.generated.h"

/**
 * 
 */
UCLASS()
class SUPERNATURAL_API UAIServiceNode : public UBTService
{
	GENERATED_BODY()
public:
	UAIServiceNode();

protected:
	// Override the Tick method to perform your service task
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
