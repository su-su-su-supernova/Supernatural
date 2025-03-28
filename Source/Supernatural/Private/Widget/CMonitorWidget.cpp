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
			// 문자 하나 지우는 함수 실행
			UE_LOG(LogTemp, Warning, TEXT(">>> [DELETE before] %s <<<"), *EnteredValue);
		}
		else if (type.Equals(TEXT("Complete")))
		{
			// 입력받은 문자열을 숫자로 변환하는 작업 실행
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
	// 문자열의 맨 마지막 문자를 지움
	EnteredValue = EnteredValue.LeftChop(1);
	UE_LOG(LogTemp, Warning, TEXT(">>> [DELETE after] %s <<<"), *EnteredValue);
}

void ACMonitorWidget::CompleteInput()
{
	// 입력받은 값을 정수로 변환
	PlayerCalculated = FCString::Atoi(*EnteredValue);

	// 입력받은 값을 DT에 반영

	// 사용자 입력값 초기화
	EnteredValue = "0";
	UE_LOG(LogTemp, Warning, TEXT(">>> [COMPLETE after] %s <<<"), *EnteredValue);
}
