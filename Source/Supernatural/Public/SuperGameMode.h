// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SuperGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SUPERNATURAL_API ASuperGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	/* Product Data Table & Data Asset */
public:
	UPROPERTY()
	class UDataTable* DTProduct;
	UPROPERTY()
	class UCProductDataAsset* DAProduct;

	void LoadCSVData(UScriptStruct* InStruct);
	void CreateDataAsset(UDataTable* InDT);
};
