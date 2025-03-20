// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProductBoxSpawner.generated.h"

UCLASS()
class SUPERNATURAL_API AProductBoxSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProductBoxSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnBoxHandler(FName a, FName ImagePath, int32 CostPrice, int32 OrderStock);

private:
	UPROPERTY()
	class UArrowComponent* ArrowComp;
	class USceneComponent* SceneComp;
	class AProductBoxActor* ProductBoxActor;
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TSubclassOf<AProductBoxActor>BoxClass;
};
