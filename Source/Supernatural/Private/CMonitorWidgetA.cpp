#include "CMonitorWidgetA.h"
#include "Components/Button.h"
#include "CMonitorButton.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Components/VerticalBox.h"


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


	UE_LOG(LogTemp, Warning, TEXT(">>> s : %s <<<"), *InputCost);
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
	UE_LOG(LogTemp, Warning, TEXT(">>> [DELETE before] %s <<<"), *InputCost);

	// 문자열의 맨 마지막 문자를 지움
	InputCost = InputCost.LeftChop(1);
	UE_LOG(LogTemp, Warning, TEXT(">>> [DELETE after] %s <<<"), *InputCost);
}

void UCMonitorWidgetA::ConvertInputToString()
{
	UE_LOG(LogTemp, Warning, TEXT(">>> [COMPLETE before] %s <<<"), *InputCost);

	// 입력받은 값을 정수로 변환
	PlayerCalculated = FCString::Atoi(*InputCost);

	// 입력받은 값을 DT에 반영

	// 사용자 입력값 초기화
	InputCost = "0";
	UE_LOG(LogTemp, Warning, TEXT(">>> [COMPLETE after] %s <<<"), *InputCost);
}

void UCMonitorWidgetA::SetWrapBox()
{
	for (int32 i = 1; i <= 12; i++)
	{
		// 버튼 생성
		MonitorButton = CreateWidget<UCMonitorButton>(this, MonitorButtonBP);
		MonitorButton->ButtonIndex = i;
		MonitorButton->SetMonitorReference(this);

		// 버튼 정보 추가
		if(i == 10)
			MonitorButton->Text->SetText(FText::FromString("<"));
		else if(i == 11)
			MonitorButton->Text->SetText(FText::AsNumber(0));
		else if(i == 12)
			MonitorButton->Text->SetText(FText::FromString(TEXT("●")));
		else
			MonitorButton->Text->SetText(FText::AsNumber(i));

		// Wrapbox에 추가
		WrapBox->AddChildToWrapBox(MonitorButton);

		UE_LOG(LogTemp, Warning, TEXT(">>> Button name : %s"), *(MonitorButton->GetName()));
	}
}

void UCMonitorWidgetA::SetVerticalBox()
{
	//TextTotalCost->SetText(FText::Format(NSLOCTEXT("UI", "TotalCost", "합계 : {0}"), TotalCost));
	//TextTotalCost->SetText(FText::Format(NSLOCTEXT("UI", "TotalCost", "합계 : {0}"), FString::FromInt(TotalCost)));
	TextTotalCost->SetText(FText::FromString(FString::Printf(TEXT("합계 : %d"), TotalCost)));
	VerticalBox->AddChildToVerticalBox(TextTotalCost);

	//TextInputCost->SetText(FText::Format(NSLOCTEXT("UI", "InputCost", "현재 금액 : {0}"), InputCost));
	TextInputCost->SetText(FText::FromString(FString::Printf(TEXT("현재 금액 : %s"), *InputCost)));
	VerticalBox->AddChildToVerticalBox(TextInputCost);
}


