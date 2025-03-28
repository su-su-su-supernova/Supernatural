#include "CMonitorWidget.h"

ACMonitorWidget::ACMonitorWidget()
{
	PrimaryActorTick.bCanEverTick = true;

	EnteredValue = "0";
}

void ACMonitorWidget::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACMonitorWidget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACMonitorWidget::OnClickButton(UButton* InButton)
{
	if (InButton)
	{
		FString name = InButton->GetName();
		FString tmp, type; 
		name.Split(TEXT("B_"), &tmp, &type);
		UE_LOG(LogTemp, Warning, TEXT(">>> Button Type : %s"), *type);

		if (type.Equals(TEXT("Delete")))
		{
			// ���� �ϳ� ����� �Լ� ����
			UE_LOG(LogTemp, Warning, TEXT(">>> [DELETE before] %s <<<"), *EnteredValue);
		}
		else if (type.Equals(TEXT("Complete")))
		{
			// �Է¹��� ���ڿ��� ���ڷ� ��ȯ�ϴ� �۾� ����
			UE_LOG(LogTemp, Warning, TEXT(">>> [COMPLETE before] %s <<<"), *EnteredValue);
		}
		else
		{
			if(EnteredValue.Equals("0"))
			{
				if(type.Equals("0")) return;
				EnteredValue = type;
				return;
			}
			EnteredValue += type;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT(">>> s : %s <<<"), *EnteredValue);
}

void ACMonitorWidget::DeleteInput()
{
	// ���ڿ��� �� ������ ���ڸ� ����
	EnteredValue = EnteredValue.LeftChop(1);
	UE_LOG(LogTemp, Warning, TEXT(">>> [DELETE after] %s <<<"), *EnteredValue);
}

void ACMonitorWidget::CompleteInput()
{
	// �Է¹��� ���� ������ ��ȯ
	PlayerCalculated = FCString::Atoi(*EnteredValue);

	// �Է¹��� ���� DT�� �ݿ�

	// ����� �Է°� �ʱ�ȭ
	EnteredValue = "0";
	UE_LOG(LogTemp, Warning, TEXT(">>> [COMPLETE after] %s <<<"), *EnteredValue);
}
