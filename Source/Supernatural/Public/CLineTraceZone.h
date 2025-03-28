#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLineTraceZone.generated.h"

UCLASS()
class SUPERNATURAL_API ACLineTraceZone : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLineTraceZone();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
    UPROPERTY(EditDefaultsOnly, Category = "LineTraceZone")
	class UBoxComponent* BoxComponent;
};
