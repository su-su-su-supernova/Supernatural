#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/Button.h"
#include "CMonitorWidget.generated.h"

UCLASS()
class SUPERNATURAL_API ACMonitorWidget : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMonitorWidget();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	int32 TotalCost;
	int32 PlayerCalculated;
	FString EnteredValue;

	void OnClickButton(UButton* InButton);
	void DeleteInput();
	void CompleteInput();
};
