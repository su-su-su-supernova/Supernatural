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
    Monitor->OnMonitorButtonClicked(Button->GetName());
}