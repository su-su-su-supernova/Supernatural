#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMonitorWidgetA.generated.h"

UCLASS()
class SUPERNATURAL_API UCMonitorWidgetA : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UCMonitorWidgetA(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

public:
    UFUNCTION(BlueprintCallable, Category = "Monitor")
    void OnMonitorButtonClicked(int32 InButtonValue);

private:
	void NumberEntered(int32 InType);
	void DeleteLastInput();
	void ConvertInputToString();

	int32 TotalCost = 30000;
	int32 PlayerCalculated = 0;
	FString InputCost = "0";

	/* Buttons*/
public:
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* WrapBox;

    class UCMonitorButton* MonitorButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI | Buttons")
    TSubclassOf<class UCMonitorButton> MonitorButtonBP;

    void SetWrapBox();

	/* Cost */
public:
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* VerticalBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextTotalCost;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextInputCost;

	void SetVerticalBox();
};
