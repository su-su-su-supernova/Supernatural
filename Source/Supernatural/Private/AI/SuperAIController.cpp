// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperAIController.h"
#include "Kismet/GameplayStatics.h"
#include "AiCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SuperGameMode.h"
#include "CPlayer.h"
#include "EAIState.h"
#include "EngineUtils.h"

ASuperAIController::ASuperAIController()
{

	ConstructorHelpers::FObjectFinder<UBehaviorTree> AIBehavior(TEXT("/Game/HWL/AI/BT_AI.BT_AI"));
	if (AIBehavior.Succeeded())AIBehaviorTree = AIBehavior.Object;
}

void ASuperAIController::BeginPlay()
{
    Super::BeginPlay();

    RunBehaviorTree(AIBehaviorTree);

    GameMode = Cast<ASuperGameMode>(GetWorld()->GetAuthGameMode());
    if (!GameMode) return;
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    ACPlayer* player = Cast<ACPlayer>(PlayerPawn);
    TArray<int32> AvailableIndices;
    for (int32 i = 0; i < GameMode->Product.Num(); i++) {
        AvailableIndices.Add(i);
    }

    // 배열 크기가 4로 고정되어 있으므로, 최대 4개만 선택
    TArray<FString> ProductNames; // FString으로 정의
    for (int i = 0; i < 4 && AvailableIndices.Num() > 0; i++) {
        int32 RandomIndex = FMath::RandRange(0, AvailableIndices.Num() - 1); // 남은 인덱스 중 하나 선택
        int32 SelectedIndex = AvailableIndices[RandomIndex]; // 선택된 인덱스
        ProductNames.Add(GameMode->GetProductDataByIndex(SelectedIndex)->ProductName); // 제품 이름 할당 (FString 가정)
        AvailableIndices.RemoveAt(RandomIndex);
    }
    BFS(ProductNames);

}

void ASuperAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool ASuperAIController::SelectNextProduct()
{
    if (index >= ProductName.Num()) {
        if (isSucceeded) return false;
        TicketNumber = GameMode->GenerateTicketNumber();
        GameMode->IncrementTicketCount();
		UE_LOG(LogTemp, Log, TEXT("%d"), TicketNumber);
        isSucceeded = true;
        return false;
    }
	FName TargetTag = FName(*ProductName[index]);
	CurrentName = ProductName[index];
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TargetTag, FoundActors);
	if (FoundActors.Num() > 0) {
		GetBlackboardComponent()->SetValueAsObject(TEXT("ProductClass"), FoundActors[0]);
		GetBlackboardComponent()->SetValueAsBool(TEXT("IsSelling"), isBuyProduct[index]);
	}
	return true;
}

void ASuperAIController::AddIndex()
{
	index++;
}

void ASuperAIController::BFS(TArray<FString>ProductNames)
{
    // 태그 검색: ProductName 4개에 대해 각각 한 번씩만 확인
    TArray<FString> MatchedTags; // 일치하는 태그를 저장할 배열
    for (const FString& Name : ProductNames) {
        // 월드에서 해당 이름과 일치하는 태그를 가진 액터를 찾음
        for (TActorIterator<AActor> It(GetWorld()); It; ++It) {
            AActor* Actor = *It;
            for (const FName& Tag : Actor->Tags) {
                if (Tag.ToString() == Name) { // FName을 FString으로 변환해 비교
                    MatchedTags.Add(Name); // 일치하면 추가
                    break; // 해당 이름에 대해 더 이상 검색할 필요 없음
                }
            }
            // 이미 찾았으면 다음 이름으로 넘어감
            if (MatchedTags.Contains(Name)) {
                break;
            }
        }
    }

    // 결과 확인 (디버깅용)
    for (const FString& MatchedTag : MatchedTags) {
        ProductName.Add(MatchedTag);
    }

}

