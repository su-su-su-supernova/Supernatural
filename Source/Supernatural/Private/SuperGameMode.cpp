#include "SuperGameMode.h"
#include "CProductDataTable.h"
#include "CProductDataAsset.h"
#include "EProductType.h"

void ASuperGameMode::BeginPlay()
{
	Super::BeginPlay();
	//LoadCSVData(FProductData::StaticStruct());
	UE_LOG(LogTemp, Error, TEXT(">> SuperBeginPlay"));
	//CreateProductDataAsset();
}

// CSV 파일에 있는 데이터로 Data Table 생성
void ASuperGameMode::LoadCSVData(UScriptStruct* InStruct)
{
	FString csvFilePath, csvFileData;

	// 파일 경로 지정
	csvFilePath = FPaths::ProjectContentDir() / TEXT("DYL/DataTables/DT_ProductDataTable.csv");
	

	// 파일명을 바탕으로 CSV 파일 데이터를 불러오는데 성공하면
	if (FFileHelper::LoadFileToString(csvFileData, *csvFilePath))
	{
		// Data Table의 Row Struct를 정의한다
		DTProduct->RowStruct = InStruct;

		// 파일 데이터를 바탕으로 Data Table을 생성한다
		TArray<FString> errorMessages = DTProduct->CreateTableFromCSVString(csvFileData);

		// Data Table 생성에 실패하면
		if (errorMessages.Num() > 0)
		{
			for(const FString err : errorMessages)
				UE_LOG(LogTemp, Error, TEXT(">> Faild to load Data Table : %s"), *err);
		}
		// Data Table 생성에 성공하면
		else
		{
			UE_LOG(LogTemp, Log, TEXT(">> Succes to load Data Table"));

			// Product Data Asset을 생성한다
			CreateProductDataAsset(DTProduct);
		}
	}
	// CSV 파일 데이터를 불러오는 데 실패했다면
	else
		UE_LOG(LogTemp, Error, TEXT(">> Faild to load CSV file from path: %s"), *csvFilePath);
}

//void ASuperGameMode::CreateProductDataAsset(UDataTable* InDT)
//{
//	// InDT에 data가 있다면
//	if (!InDT)
//	{
//		UE_LOG(LogTemp, Warning, TEXT(">> Data Table is null"));
//		return;
//	}
//
//	// enum 정보 가져오기
//	UEnum* enumData = StaticEnum<EProductType>();
//	if (!enumData)
//	{
//		UE_LOG(LogTemp, Error, TEXT(">> Failed to find EProductType enum"));
//		return;
//	}
//
//	int32 productNum = static_cast<int32>(EProductType::MAX);
//
//	// 데이터 테이블의 데이터를 로드한다
//	for (int i = 0; i < productNum; i++)
//	{
//		// 1. 행의 이름(Key)를 가져온다
//		EProductType type = static_cast<EProductType>(i);
//		FName rowName = FName(enumData->GetNameStringByIndex(i));
//
//		// 2. 행의 데이터를 가져온다
//		FProductData* rowData = InDT->FindRow<FProductData>(rowName,"");
//
//		if (!rowData)
//		{
//			UE_LOG(LogTemp, Warning, TEXT(">> Row %s not found in Data Table"), *rowName.ToString());
//			continue;
//		}
//
//		// 3. Product Data Asset 객체를 생성한다
//		UCProductDataAsset* newProductDataAsset = NewObject<UCProductDataAsset>(this, UCProductDataAsset::StaticClass());
//		if (!newProductDataAsset)
//		{
//			UE_LOG(LogTemp, Error, TEXT("Failed to create Data Asset for %s!"), *rowName.ToString());
//			continue;
//		}
//
//		// 4. Data Asset의 Product 맵에 데이터를 추가한다
//		newProductDataAsset->Product.Add(type, *rowData);
//
//		UE_LOG(LogTemp, Log, TEXT("Added %s to Product Data Asset."), *rowName.ToString());
//	}
//}


