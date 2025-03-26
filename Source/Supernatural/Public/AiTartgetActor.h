// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AiTartgetActor.generated.h"

UCLASS()
class SUPERNATURAL_API AAiTartgetActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAiTartgetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class UBoxComponent* BoxComp;

private:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
