// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CProductDataTable.h"
#include "SuperAIController.generated.h"

/**
 *
 */
UCLASS()
class SUPERNATURAL_API ASuperAIController : public AAIController
{
	GENERATED_BODY()

	ASuperAIController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds)override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviorTree;
private:
	int32 randomVaule = 0;
	class ASuperGameMode* GameMode;

	FString ProductName[4] = {};
	bool isBuyProduct[4] = { false, false, false, false };

	int32 index = 0;

	void SelectNextProduct();
};
