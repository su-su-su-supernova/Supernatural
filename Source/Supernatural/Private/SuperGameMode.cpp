#include "SuperGameMode.h"
#include "CProductDataTable.h"
#include "CProductDataAsset.h"

void ASuperGameMode::BeginPlay()
{
	Super::BeginPlay();
	LoadCSVData(FProductData::StaticStruct());
}

void ASuperGameMode::LoadCSVData(UScriptStruct* InStruct)
{
	FString csvFilePath, csvFileData;

	// ���� ��� ����
	csvFilePath = FPaths::ProjectContentDir() / TEXT("DYL/DataTables/DT_ProductDataTable.csv");

	// ���ϸ��� �������� ���� �����͸� �ҷ����µ� �����ϸ�
	if (FFileHelper::LoadFileToString(csvFileData, *csvFilePath))
	{
		// Data Table�� Row Struct�� �����Ѵ�
		DTProduct->RowStruct = InStruct;

		// ���� �����͸� �������� Data Table�� �����Ѵ�
		TArray<FString> errorMessage = DTProduct->CreateTableFromCSVString(csvFileData);
	}
}

void ASuperGameMode::CreateDataAsset(UDataTable* InDT)
{
	// ������ ���̺��� �����͸� �ε��Ѵ�

	// 
}

