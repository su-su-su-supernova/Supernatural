#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMonitorWidgetA.generated.h"

UCLASS()
class SUPERNATURAL_API UCMonitorWidgetA : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
    UFUNCTION(BlueprintCallable, Category = "Monitor")
    void OnMonitorButtonClicked(FString InButtonName);

private:
	void NumberEntered(FString InType);
	void DeleteLastInput(FString InType);
	void ConvertInputToString(FString InType);

	int32 TotalCost = 0;
	int32 PlayerCalculated = 0;
	FString EnteredValue = "0";

public:
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* WrapBox;

	class UCMonitorButton* MonitorButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buttons")
	TSubclassOf<class UCMonitorButton> MonitorButtonBP;

	void SetWrapBox();
};
