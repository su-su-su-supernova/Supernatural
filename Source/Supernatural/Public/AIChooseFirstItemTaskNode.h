// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CProductDataTable.h"
#include "AIChooseFirstItemTaskNode.generated.h"

/**
 *
 */
UCLASS()
class SUPERNATURAL_API UAIChooseFirstItemTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

    UAIChooseFirstItemTaskNode();

public:
    // 태스크가 시작될 때 호출되며, 주요 로직을 실행하고 결과를 반환합니다.
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    // 태스크가 "진행 중" 상태일 때 매 프레임 호출되어 업데이트 로직을 처리합니다.
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

    // 태스크가 중단(abort)될 때 호출되어 정리 작업을 수행합니다.
    virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;





};
