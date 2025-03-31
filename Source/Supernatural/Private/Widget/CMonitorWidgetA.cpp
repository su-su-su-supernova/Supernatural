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
#include "SuperGameMode.h"
#include "CCounter.h"


UCMonitorWidgetA::UCMonitorWidgetA(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) // 부모 클래스 초기화
{
}

void UCMonitorWidgetA::NativeConstruct()
{
	Super::NativeConstruct();
	SetWrapBox();

	SetVerticalBox();

	SuperGameMode = Cast<ASuperGameMode>(GetWorld()->GetAuthGameMode());
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
		UE_LOG(LogTemp, Warning, TEXT(">>> Input Cost : %s"), *InputCost);
		return;
	}
	InputCost += value;

	// UI 갱신
	SetTextInputCost();

	UE_LOG(LogTemp, Warning, TEXT(">>> Input Cost : %s"), *InputCost);
}

void UCMonitorWidgetA::DeleteLastInput()
{
	if(InputCost.Equals("0")) return;
	else if(InputCost.Len() == 1) InputCost = "0";
	// 문자열의 맨 마지막 문자를 지움
	else InputCost = InputCost.LeftChop(1);

	// UI 갱신
	SetTextInputCost();

	UE_LOG(LogTemp, Warning, TEXT(">>> Input Cost : %s"), *InputCost);
}

void UCMonitorWidgetA::ConvertInputToString()
{
	UE_LOG(LogTemp, Warning, TEXT(">>>> Before Update TotalSales : %d"), SuperGameMode->GetTotalSales());
	// 입력받은 값을 정수로 변환
	PlayerCalculated = FCString::Atoi(*InputCost);

	// 현재 사용자가 입력한 물품들의 총액이 얼마인지 Game Mode에 Update한다
	SuperGameMode->SetCurrentInputCost(PlayerCalculated);
	
	// Player가 입력한 값이 총 계산해야 할 금액과 다르면 Input Cost를 0으로 초기화하여 
	// 사용자로 하여금 다시 값을 입력하도록 한다
	if(SuperGameMode->GetCurrentInputCost() != SuperGameMode->GetCurrentTotalCost())
	{
		InputCost = "0";

		// UI 갱신
		SetTextInputCost();
		return;
	}

	// 매출을 갱신한다
	SuperGameMode->SetTotalSales( SuperGameMode->GetTotalSales() + PlayerCalculated );
	UE_LOG(LogTemp, Warning, TEXT(">>> After Update TotalSales : %d"), SuperGameMode->GetTotalSales());

	// 사용자 입력값 초기화
	InputCost = "0";
	SuperGameMode->SetCurrentTotalCost(0);
	SuperGameMode->SetCurrentInputCost(0);

	UE_LOG(LogTemp, Warning, TEXT(">>> Input Cost : %s"), *InputCost);
    UE_LOG(LogTemp, Log, TEXT("[Reset] CurCheckoutTotal : %d / CurInputTotal : %d"), SuperGameMode->GetCurrentTotalCost(), SuperGameMode->GetCurrentInputCost());

	SuperGameMode->GetCounter()->ReadyToNextCustomer();
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
	/*TextTotalCost->SetText(FText::FromString(FString::Printf(TEXT("합계 : %d"), TotalCost)));*/
	SetTextTotalCost();
	VerticalBox->AddChildToVerticalBox(TextTotalCost);

	/*TextInputCost->SetText(FText::FromString(FString::Printf(TEXT("현재 금액 : %s"), *InputCost)));*/
	SetTextInputCost();
	VerticalBox->AddChildToVerticalBox(TextInputCost);
}

void UCMonitorWidgetA::SetTextTotalCost()
{
	UE_LOG(LogTemp, Error, TEXT("[MonitorWidget] TextTotalSetting"));

	UE_LOG(LogTemp, Error, TEXT("[MonitorWidget] TextTotalSetting : %d"),TotalCost);

	TextTotalCost->SetText(FText::Format(FText::FromString(TEXT("합계 : {0}")), TotalCost));
}

void UCMonitorWidgetA::SetTextInputCost()
{
	TextInputCost->SetText(FText::FromString(FString::Printf(TEXT("현재 금액 : %s"), *InputCost)));
}


