#include "CMonitorWidgetA.h"
#include "Components/Button.h"
#include "CMonitorButton.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Components/VerticalBox.h"
#include "SlateBasics.h"        // Slate 기본 기능
#include "SlateCore.h"          // SlateCore 관련 (FSlateBrush 등)
#include "Styling/SlateTypes.h" // FButtonStyle 정의
#include "Styling/SlateColor.h" // FSlateColor 관련
#include "Widgets/Input/SButton.h" // SButton 위젯 관련
#include "../../../../../../../Source/Runtime/UMG/Public/Components/CanvasPanelSlot.h"


UCMonitorWidgetA::UCMonitorWidgetA(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) // 부모 클래스 초기화
{
}

void UCMonitorWidgetA::NativeConstruct()
{
	Super::NativeConstruct();
	SetWrapBox();

	SetVerticalBox();

}


void UCMonitorWidgetA::OnMonitorButtonClicked(int32 InButtonValue)
{
	switch (InButtonValue)
	{
		case 10:
			DeleteLastInput();
			break;
		case 12:
			ConvertInputToString();
			break;
		default:
			NumberEntered(InButtonValue);
			break;
	}
}

void UCMonitorWidgetA::NumberEntered(int32 InType)
{
	FString value = InType == 11 ? "0" : FString::FromInt(InType);
	if (InputCost.Equals("0"))
	{
		if (InType == 11) return;
		InputCost = value;
		return;
	}
	InputCost += value;
}

void UCMonitorWidgetA::DeleteLastInput()
{
	if(InputCost.Equals("0")) return;
	else if(InputCost.Len() == 1) InputCost = "0";
	// 문자열의 맨 마지막 문자를 지움
	else InputCost = InputCost.LeftChop(1);
}

void UCMonitorWidgetA::ConvertInputToString()
{
	// 입력받은 값을 정수로 변환
	PlayerCalculated = FCString::Atoi(*InputCost);

	// 입력받은 값을 DT에 반영

	// 사용자 입력값 초기화
	InputCost = "0";
}

void UCMonitorWidgetA::SetWrapBox()
{
	for (int32 i = 1; i <= 12; i++)
	{
		// 버튼 생성
		MonitorButton = CreateWidget<UCMonitorButton>(this, MonitorButtonBP);
		MonitorButton->ButtonIndex = i;
		MonitorButton->SetMonitorReference(this);

		FButtonStyle buttonStyle;
		FSlateBrush normalBrush, hoveredBrush, pressedBrush;

        normalBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
        normalBrush.OutlineSettings.CornerRadii = FVector4(0.5f, 0.5f, 0.5f, 0.5f);

        hoveredBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
        hoveredBrush.OutlineSettings.CornerRadii = FVector4(0.5f, 0.5f, 0.5f, 0.5f);

        pressedBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
        pressedBrush.OutlineSettings.CornerRadii = FVector4(0.5f, 0.5f, 0.5f, 0.5f);

        switch (i)
        {
        case 10:
            MonitorButton->Text->SetText(FText::FromString("<"));
            normalBrush.TintColor = FSlateColor(FLinearColor(FColor::FromHex(TEXT("F45892FF"))));
            hoveredBrush.TintColor = FSlateColor(FLinearColor(FColor::FromHex(TEXT("F4B0C3FF"))));
            pressedBrush.TintColor = FSlateColor(FLinearColor(FColor::FromHex(TEXT("9B355CFF"))));

            break;
        case 11:
            MonitorButton->Text->SetText(FText::AsNumber(0));
            normalBrush.TintColor = FSlateColor(FLinearColor(FColor::FromHex(TEXT("638ABBFF"))));
            hoveredBrush.TintColor = FSlateColor(FLinearColor(FColor::FromHex(TEXT("D9D9D9FF"))));
            pressedBrush.TintColor = FSlateColor(FLinearColor(FColor::FromHex(TEXT("1C3B6AFF"))));
            break;
        case 12:
            MonitorButton->Text->SetText(FText::FromString(TEXT("●")));
            normalBrush.TintColor = FSlateColor(FLinearColor(FColor::FromHex(TEXT("7FD365FF"))));
            hoveredBrush.TintColor = FSlateColor(FLinearColor(FColor::FromHex(TEXT("B0D3A9FF"))));
            pressedBrush.TintColor = FSlateColor(FLinearColor(FColor::FromHex(TEXT("407032FF"))));
            break;
        default:
            MonitorButton->Text->SetText(FText::AsNumber(i));
            normalBrush.TintColor = FSlateColor(FLinearColor(FColor::FromHex(TEXT("638ABBFF"))));
            hoveredBrush.TintColor = FSlateColor(FLinearColor(FColor::FromHex(TEXT("D9D9D9FF"))));
            pressedBrush.TintColor = FSlateColor(FLinearColor(FColor::FromHex(TEXT("1C3B6AFF"))));
            break;
        }

        buttonStyle.SetNormal(normalBrush);
        buttonStyle.SetHovered(hoveredBrush);
        buttonStyle.SetPressed(pressedBrush);

        MonitorButton->Button->SetStyle(buttonStyle);

		// Wrapbox에 추가
		WrapBox->AddChildToWrapBox(MonitorButton);
	}
}

void UCMonitorWidgetA::SetVerticalBox()
{
	TextTotalCost->SetText(FText::FromString(FString::Printf(TEXT("합계 : %d"), TotalCost)));
	VerticalBox->AddChildToVerticalBox(TextTotalCost);

	TextInputCost->SetText(FText::FromString(FString::Printf(TEXT("현재 금액 : %s"), *InputCost)));
	VerticalBox->AddChildToVerticalBox(TextInputCost);
}


