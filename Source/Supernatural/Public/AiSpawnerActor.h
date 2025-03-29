// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AiCharacter.h"
#include "AiSpawnerActor.generated.h"

UCLASS()
class SUPERNATURAL_API AAiSpawnerActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAiSpawnerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class UArrowComponent* ArrowComp;
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AAiCharacter> AiCharacterSample;

	float CurrentTime = 0.0f;

};
