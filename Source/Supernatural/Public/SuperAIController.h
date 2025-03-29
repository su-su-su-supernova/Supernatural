// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CProductDataTable.h"
#include "EAIState.h"
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

public:
	TArray<FString> ProductName;
	FString CurrentName;

	UPROPERTY(VisibleAnywhere)
	TArray<bool> isBuyProduct = { false, false, false, false };
	TArray<FString>SearchFailedProduct;
	UPROPERTY(VisibleAnywhere)
	int32 index = 0;
public:
	bool SelectNextProduct();
	void AddIndex();
	void BFS(TArray<FString>ProductNames);

public:
	FVector TargetLocation;
	EAIState AIState = EAIState::FindProduct;
	TArray<AActor*> FoundActors;
	int32 TicketNumber = 0;

	bool isSucceeded = false;

};
