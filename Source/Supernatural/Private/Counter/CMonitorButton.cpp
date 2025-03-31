#include "CMonitorButton.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "CMonitorWidgetA.h"
#include "CCounter.h"

void UCMonitorButton::NativeConstruct()
{
    Super::NativeConstruct();
    Button->OnClicked.AddDynamic(this, &UCMonitorButton::OnButtonClicked);
}

void UCMonitorButton::OnButtonClicked()
{
    // UE_LOG(LogTemp, Warning, TEXT(">>>>> %s : %d <<<<<"), *(Button->GetName()), ButtonIndex);
    MonitorWidget->OnMonitorButtonClicked(ButtonIndex);
}

void UCMonitorButton::SetMonitorReference(UCMonitorWidgetA* InMonitorWidget)
{
    MonitorWidget = InMonitorWidget;
}
