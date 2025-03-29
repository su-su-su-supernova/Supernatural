#include "SuperGameMode.h"
#include "EProductType.h"

ASuperGameMode::ASuperGameMode()
{
    // DTProduct를 CreateDefaultSubobject로 초기화
    DTProduct = CreateDefaultSubobject<UDataTable>(TEXT("ProductDataTable"));

    // CSV 파일 로드 및 DataTable 초기화
    LoadProductDT(FProductData::StaticStruct());
}

void ASuperGameMode::BeginPlay()
{
    Super::BeginPlay();
    //UE_LOG(LogTemp, Log, TEXT(">> SuperBeginPlay"));
}

void ASuperGameMode::LoadProductDT(UScriptStruct* InStruct)
{
    FString csvFilePath, csvFileData;

    // 파일 경로 지정
    csvFilePath = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("DYL/DataTables/DT_ProductData.csv"));

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
            for (const FString& err : errorMessages)
                UE_LOG(LogTemp, Error, TEXT(">> Failed to load Data Table : %s"), *err);
        }
        // Data Table 생성에 성공하면
        else
        {
            UE_LOG(LogTemp, Warning, TEXT(">> Success to load Data Table"));

            // Product Data Table에서 각 행을 꺼내와서 TMap에 저장한다
            LoadProductData();
        }
    }
    // CSV 파일 데이터를 불러오는 데 실패했다면
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

    // DataTable의 모든 행을 가져온다
    static const FString contextString(TEXT("Product Data Context"));
    TArray<FName> rowNames = DTProduct->GetRowNames();

    for (const FName& rowName : rowNames)
    {
        FProductData* rowData = DTProduct->FindRow<FProductData>(rowName, contextString);

        // 데이터가 있으면 Product TMap에 추가
        if (rowData) Product.Add(rowData->ProductName, rowData);
        // 없으면 로그 출력
        else UE_LOG(LogTemp, Warning, TEXT(">> Failed to find row : %s"), *rowName.ToString());
    }

    UE_LOG(LogTemp, Error, TEXT(">> Product Data Success. Total items : %d"), Product.Num());

    for (auto p : Product)
    {
        UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>> Product : %s / Enum : %d"), *p.Key, p.Value->ProductEnum);
    }
}

int32 ASuperGameMode::GenerateTicketNumber()
{
    return TicketNumber;
}

void ASuperGameMode::IncrementTicketCount()
{
    TicketNumber++;
}

void ASuperGameMode::IncrementGameModeTicketCount()
{
    GameModeTicketNumber++;
}

int32 ASuperGameMode::GenerateGameModeTicketNumber()
{
    UE_LOG(LogTemp, Log, TEXT("TICK%d"), GameModeTicketNumber);

    return GameModeTicketNumber;
}

FProductData* ASuperGameMode::GetProductData(const FString& ProductName) const
{
    FProductData* const* FoundData = Product.Find(ProductName);
    if (FoundData)
    {
        return *FoundData; // 포인터 직접 반환
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT(">> Product '%s' not found in Product map"), *ProductName);
        return nullptr;
    }
}
FProductData* ASuperGameMode::GetProductDataByIndex(int32 Index) const
{
    if (Product.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT(">> Product map is empty"));
        return nullptr;
    }

    if (Index < 0 || Index >= Product.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT(">> Index %d is out of range. Product map size: %d"), Index, Product.Num());
        return nullptr;
    }

    int32 CurrentIndex = 0;
    for (const auto& Pair : Product)
    {
        if (CurrentIndex == Index)
        {
            return Pair.Value; // 포인터 직접 반환
        }
        CurrentIndex++;
    }
    return nullptr;
}