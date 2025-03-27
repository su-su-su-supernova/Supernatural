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

		// ���ڿ��� �� ������ ���ڸ� ����
		if (type.Equals(TEXT("Delete"))) 
			DeleteLastInput(type);
		// �Է¹��� ���ڿ��� ���ڷ� ��ȯ�ϴ� �۾� ����
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

	// ���ڿ��� �� ������ ���ڸ� ����
	EnteredValue = EnteredValue.LeftChop(1);
	UE_LOG(LogTemp, Warning, TEXT(">>> [DELETE after] %s <<<"), *EnteredValue);
}

void UCMonitorWidgetA::ConvertInputToString(FString InType)
{
	UE_LOG(LogTemp, Warning, TEXT(">>> [COMPLETE before] %s <<<"), *EnteredValue);

	// �Է¹��� ���� ������ ��ȯ
	PlayerCalculated = FCString::Atoi(*EnteredValue);

	// �Է¹��� ���� DT�� �ݿ�

	// ����� �Է°� �ʱ�ȭ
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
