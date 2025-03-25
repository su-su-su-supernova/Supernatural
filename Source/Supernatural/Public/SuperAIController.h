// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
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
	void FindActor(APawn* PlayerPawn);

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviorTree;

};
