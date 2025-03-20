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

// CSV ���Ͽ� �ִ� �����ͷ� Data Table ����
void ASuperGameMode::LoadCSVData(UScriptStruct* InStruct)
{
	FString csvFilePath, csvFileData;

	// ���� ��� ����
	csvFilePath = FPaths::ProjectContentDir() / TEXT("DYL/DataTables/DT_ProductDataTable.csv");
	

	// ���ϸ��� �������� CSV ���� �����͸� �ҷ����µ� �����ϸ�
	if (FFileHelper::LoadFileToString(csvFileData, *csvFilePath))
	{
		// Data Table�� Row Struct�� �����Ѵ�
		DTProduct->RowStruct = InStruct;

		// ���� �����͸� �������� Data Table�� �����Ѵ�
		TArray<FString> errorMessages = DTProduct->CreateTableFromCSVString(csvFileData);

		// Data Table ������ �����ϸ�
		if (errorMessages.Num() > 0)
		{
			for(const FString err : errorMessages)
				UE_LOG(LogTemp, Error, TEXT(">> Faild to load Data Table : %s"), *err);
		}
		// Data Table ������ �����ϸ�
		else
		{
			UE_LOG(LogTemp, Log, TEXT(">> Succes to load Data Table"));

			// Product Data Asset�� �����Ѵ�
			CreateProductDataAsset(DTProduct);
		}
	}
	// CSV ���� �����͸� �ҷ����� �� �����ߴٸ�
	else
		UE_LOG(LogTemp, Error, TEXT(">> Faild to load CSV file from path: %s"), *csvFilePath);
}

//void ASuperGameMode::CreateProductDataAsset(UDataTable* InDT)
//{
//	// InDT�� data�� �ִٸ�
//	if (!InDT)
//	{
//		UE_LOG(LogTemp, Warning, TEXT(">> Data Table is null"));
//		return;
//	}
//
//	// enum ���� ��������
//	UEnum* enumData = StaticEnum<EProductType>();
//	if (!enumData)
//	{
//		UE_LOG(LogTemp, Error, TEXT(">> Failed to find EProductType enum"));
//		return;
//	}
//
//	int32 productNum = static_cast<int32>(EProductType::MAX);
//
//	// ������ ���̺��� �����͸� �ε��Ѵ�
//	for (int i = 0; i < productNum; i++)
//	{
//		// 1. ���� �̸�(Key)�� �����´�
//		EProductType type = static_cast<EProductType>(i);
//		FName rowName = FName(enumData->GetNameStringByIndex(i));
//
//		// 2. ���� �����͸� �����´�
//		FProductData* rowData = InDT->FindRow<FProductData>(rowName,"");
//
//		if (!rowData)
//		{
//			UE_LOG(LogTemp, Warning, TEXT(">> Row %s not found in Data Table"), *rowName.ToString());
//			continue;
//		}
//
//		// 3. Product Data Asset ��ü�� �����Ѵ�
//		UCProductDataAsset* newProductDataAsset = NewObject<UCProductDataAsset>(this, UCProductDataAsset::StaticClass());
//		if (!newProductDataAsset)
//		{
//			UE_LOG(LogTemp, Error, TEXT("Failed to create Data Asset for %s!"), *rowName.ToString());
//			continue;
//		}
//
//		// 4. Data Asset�� Product �ʿ� �����͸� �߰��Ѵ�
//		newProductDataAsset->Product.Add(type, *rowData);
//
//		UE_LOG(LogTemp, Log, TEXT("Added %s to Product Data Asset."), *rowName.ToString());
//	}
//}


