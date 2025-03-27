// Fill out your copyright notice in the Description page of Project Settings.


#include "CMonitorWidgetA.h"
#include "Components/Button.h"
#include "CMonitorButton.h"

void UCMonitorWidgetA::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCMonitorWidgetA::OnMonitorButtonClicked(FString InButtonName)
{
	if (!InButtonName.IsEmpty())
	{
		FString tmp, type;
		InButtonName.Split(TEXT("B_"), &tmp, &type);
		UE_LOG(LogTemp, Warning, TEXT(">>> Button Type : %s"), *type);

		// 문자열의 맨 마지막 문자를 지움
		if (type.Equals(TEXT("Delete"))) 
			DeleteLastInput(type);
		// 입력받은 문자열을 숫자로 변환하는 작업 실행
		else if (type.Equals(TEXT("Complete"))) 
			ConvertInputToString(type);
		else 
			NumberEntered(type);
	}

	UE_LOG(LogTemp, Warning, TEXT(">>> s : %s <<<"), *EnteredValue);
}

void UCMonitorWidgetA::NumberEntered(FString InType)
{
	if (EnteredValue.Equals("0"))
	{
		if (InType.Equals("0")) return;
		EnteredValue = InType;
		return;
	}
	EnteredValue += InType;
}

void UCMonitorWidgetA::DeleteLastInput(FString InType)
{
	UE_LOG(LogTemp, Warning, TEXT(">>> [DELETE before] %s <<<"), *EnteredValue);

	// 문자열의 맨 마지막 문자를 지움
	EnteredValue = EnteredValue.LeftChop(1);
	UE_LOG(LogTemp, Warning, TEXT(">>> [DELETE after] %s <<<"), *EnteredValue);
}

void UCMonitorWidgetA::ConvertInputToString(FString InType)
{
	UE_LOG(LogTemp, Warning, TEXT(">>> [COMPLETE before] %s <<<"), *EnteredValue);

	// 입력받은 값을 정수로 변환
	PlayerCalculated = FCString::Atoi(*EnteredValue);

	// 입력받은 값을 DT에 반영

	// 사용자 입력값 초기화
	EnteredValue = "0";
	UE_LOG(LogTemp, Warning, TEXT(">>> [COMPLETE after] %s <<<"), *EnteredValue);
}

void UCMonitorWidgetA::SetWrapBox()
{
	for (int i = 0; i < 12; i++)
	{
		MonitorButton = CreateWidget<UCMonitorButton>(this, MonitorButtonBP);
		//MonitorButton->Text = SetText();

	}
}
