#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CComputer.generated.h"

// ���� ����
class UCProductDataAsset;

UCLASS()
class SUPERNATURAL_API ACComputer : public AActor
{
	GENERATED_BODY()
	
public:	
	ACComputer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


};
