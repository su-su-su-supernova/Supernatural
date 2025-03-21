#include "SuperGameMode.h"
#include "EProductType.h"

ASuperGameMode::ASuperGameMode()
{
    // DTProduct�� CreateDefaultSubobject�� �ʱ�ȭ
    DTProduct = CreateDefaultSubobject<UDataTable>(TEXT("ProductDataTable"));

    // CSV ���� �ε� �� DataTable �ʱ�ȭ
    LoadProductDT(FProductData::StaticStruct());
}

void ASuperGameMode::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT(">> SuperBeginPlay"));
}

void ASuperGameMode::LoadProductDT(UScriptStruct* InStruct)
{
    FString csvFilePath, csvFileData;

    // ���� ��� ����
    csvFilePath = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("DYL/DataTables/DT_ProductData.csv"));

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
            for (const FString& err : errorMessages)
                UE_LOG(LogTemp, Error, TEXT(">> Failed to load Data Table : %s"), *err);
        }
        // Data Table ������ �����ϸ�
        else
        {
            UE_LOG(LogTemp, Warning, TEXT(">> Success to load Data Table"));

            // Product Data Table���� �� ���� �����ͼ� TMap�� �����Ѵ�
            LoadProductData();
        }
    }
    // CSV ���� �����͸� �ҷ����� �� �����ߴٸ�
    else
        UE_LOG(LogTemp, Error, TEXT(">> Failed to load CSV file from path: %s"), *csvFilePath);
}

void ASuperGameMode::LoadProductData()
{
    if (!DTProduct)
    {
        UE_LOG(LogTemp, Error, TEXT(">> DTProduct is not set"));
        return;
    }

    // DataTable�� ��� ���� �����´�
    static const FString contextString(TEXT("Product Data Context"));
    TArray<FName> rowNames = DTProduct->GetRowNames();

    for (const FName& rowName : rowNames)
    {
        FProductData* rowData = DTProduct->FindRow<FProductData>(rowName, contextString);

        // �����Ͱ� ������ Product TMap�� �߰�
        if (rowData) Product.Add(rowData->ProductName, rowData);
        // ������ �α� ���
        else UE_LOG(LogTemp, Warning, TEXT(">> Failed to find row : %s"), *rowName.ToString());
    }

    UE_LOG(LogTemp, Error, TEXT(">> Product Data Success. Total items : %d"), Product.Num());

    for (auto p : Product)
    {
        UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>> Product : %s / Price : %d"), *p.Key, p.Value->SellingPrice);
    }
}