#include "CMonitorButton.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "CMonitorWidgetA.h"

void UCMonitorButton::NativeConstruct()
{
    Super::NativeConstruct();
    Button->OnClicked.AddDynamic(this, &UCMonitorButton::OnButtonClicked);
}

void UCMonitorButton::OnButtonClicked()
{
    MonitorWidget->OnMonitorButtonClicked(ButtonIndex);
}

void UCMonitorButton::SetMonitorReference(UCMonitorWidgetA* InMonitorWidget)
{
    MonitorWidget = InMonitorWidget;
}
