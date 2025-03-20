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

	// 파일 경로 지정
	csvFilePath = FPaths::ProjectContentDir() / TEXT("DYL/DataTables/DT_ProductDataTable.csv");

	// 파일명을 바탕으로 파일 데이터를 불러오는데 성공하면
	if (FFileHelper::LoadFileToString(csvFileData, *csvFilePath))
	{
		// Data Table의 Row Struct를 정의한다
		DTProduct->RowStruct = InStruct;

		// 파일 데이터를 바탕으로 Data Table을 생성한다
		TArray<FString> errorMessage = DTProduct->CreateTableFromCSVString(csvFileData);
	}
}

void ASuperGameMode::CreateDataAsset(UDataTable* InDT)
{
	// 데이터 테이블의 데이터를 로드한다

	// 
}

