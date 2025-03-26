#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCounter.generated.h"

UCLASS()
class SUPERNATURAL_API ACCounter : public AActor
{
	GENERATED_BODY()
	
public:	
	ACCounter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* CounterBody;
	UPROPERTY(EditAnywhere)
	class UStaticMesh* BodyMesh;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* CounterMonitor;
	UPROPERTY(EditAnywhere)
	class UStaticMesh* MonitorMesh;
	UPROPERTY(EditAnywhere)
	class UMaterial* MonitorMat;
	
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* WidgetComponent;

	/*UPROPERTY(EditAnywhere)
	TSubclassOf<class UCounterMonitorWidget> MonitorWidget;*/

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* CasherBody;
	UPROPERTY(EditAnywhere)
	class UStaticMesh* CasherMesh;
};
