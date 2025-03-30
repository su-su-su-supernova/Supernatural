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
    TArray<EProductType> ProductNames; // FString으로 정의
    for (int i = 0; i < 4 && AvailableIndices.Num() > 0; i++) {
        int32 RandomIndex = FMath::RandRange(0, AvailableIndices.Num() - 1);
        int32 SelectedIndex = AvailableIndices[RandomIndex];
        if (!GameMode) return;
        EProductType ProductType = static_cast<EProductType>(i);
        ProductNames.Add(GameMode->GetProductData(ProductType)->ProductEnum);
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

void ASuperAIController::BFS(TArray<EProductType> ProductNames)
{

    TArray<FName> MatchedTags; // 일치하는 태그 저장

    for (const EProductType& ProductType : ProductNames)
    {
        // EProductType 값을 FName으로 변환
        FName ProductNameAsFName = FName(*UEnum::GetValueAsString(ProductType));

        // 월드에서 태그 검색
        for (TActorIterator<AActor> It(GetWorld()); It; ++It)
        {
            AActor* Actor = *It;
            if (Actor->Tags.Contains(ProductNameAsFName)) // 태그가 있는지 바로 체크
            {
                MatchedTags.Add(ProductNameAsFName);
                break; // 하나만 찾으면 루프 탈출
            }
        }
    }

    // 디버깅 출력
    for (const FName& MatchedTag : MatchedTags)
    {
        UE_LOG(LogTemp, Warning, TEXT("Matched Tag Found: %s"), *MatchedTag.ToString());
        ProductName.Add(*MatchedTag.ToString());
    }
}