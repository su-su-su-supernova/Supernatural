#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMonitorButton.generated.h"

UCLASS()
class SUPERNATURAL_API UCMonitorButton : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	class UCMonitorWidgetA* MonitorWidget;

	UFUNCTION()
	void OnButtonClicked();

	void SetMonitorReference(UCMonitorWidgetA* InMonitorWidget);

	int32 ButtonIndex;
};
