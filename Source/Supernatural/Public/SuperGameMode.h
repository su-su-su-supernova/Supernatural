#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SuperGameMode.generated.h"

class CProductDataTable;

UCLASS()
class SUPERNATURAL_API ASuperGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	/* Product Data Table & Data Asset */
public:
	UPROPERTY(EditAnywhere, Category = "DataTable")
	class UDataTable* DTProduct;

	UPROPERTY(EditAnywhere, Category = "DataAsset")
	class UCProductDataAsset* DAProduct;

	void LoadCSVData(UScriptStruct* InStruct);

	// void CreateProductDataAsset(UDataTable* InDT);

	void 
};
