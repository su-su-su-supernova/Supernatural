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
#include "salesStandActor.h" // AsalesStandActor 포함
#include "Components/BoxComponent.h"

ASuperAIController::ASuperAIController()
{
    ConstructorHelpers::FObjectFinder<UBehaviorTree> AIBehavior(TEXT("/Game/HWL/AI/BT_AI.BT_AI"));
    if (AIBehavior.Succeeded()) AIBehaviorTree = AIBehavior.Object;
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

    TArray<EProductType> ProductNames;
    for (int i = 0; i < 4 && AvailableIndices.Num() > 0; i++) {
        int32 RandomIndex = FMath::RandRange(0, AvailableIndices.Num() - 1);
        int32 SelectedIndex = AvailableIndices[RandomIndex];
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
    if (ProductName.Num() == 0) {
        TicketNumber = -1;
        return false;
    }
    if (index >= ProductName.Num()&& ProductName.Num() != 0) {
        if (isSucceeded) return false;
        GameMode->WaitingAIs.Enqueue(GameMode->GenerateTicketNumber());
        TicketNumber = GameMode->GenerateTicketNumber();
        GameMode->IncrementTicketCount();
        isSucceeded = true;
        return false;
    }
    FindActor();
    FName TargetTag = FName(*ProductName[index]);
    CurrentName = ProductName[index];
    // 컴포넌트 검색
    TArray<USceneComponent*> FoundComponents;
    for (TActorIterator<AsalesStandActor> It(GetWorld()); It; ++It)
    {
        AsalesStandActor* SalesStandActor = *It;
        if (!SalesStandActor || !SalesStandActor->TargetComp) continue;
        if (SalesStandActor->TargetComp->ComponentHasTag(TargetTag))
        {
            FoundComponents.Add(SalesStandActor->TargetComp);
            break;
        }
    }

    if (FoundComponents.Num() > 0) {
        // 컴포넌트의 월드 위치를 가져와서 블랙보드에 저장
        FVector ComponentLocation = FoundComponents[0]->GetComponentLocation();
        GetBlackboardComponent()->SetValueAsVector(TEXT("ProductClass"), ComponentLocation);
        return true;
    }
    return true;

}

void ASuperAIController::AddIndex()
{
    index++;
}

void ASuperAIController::BFS(TArray<EProductType> ProductNames)
{
    TArray<USceneComponent*> MatchedComponents;

    for (TActorIterator<AsalesStandActor> It(GetWorld()); It; ++It)
    {
        AsalesStandActor* SalesStandActor = *It;
        if (!SalesStandActor) continue;

        UBoxComponent* TargetComp = SalesStandActor->TargetComp;
        if (!TargetComp) continue;

        for (const EProductType& ProductType : ProductNames)
        {
            FName ProductNameAsFName = FName(*UEnum::GetValueAsString(ProductType));
			if (TargetComp->ComponentHasTag(ProductNameAsFName))
			{
                if (MatchedComponents.Contains(TargetComp)) return;
                if (ProductName.Contains(*ProductNameAsFName.ToString())) return;
				MatchedComponents.Add(TargetComp);
				ProductName.Add(*ProductNameAsFName.ToString());
				break;
			}
        }
    }

}

bool ASuperAIController::FindActor()
{
    for (TActorIterator<AsalesStandActor> It(GetWorld()); It; ++It)
    {
        AsalesStandActor* SalesStandActor = *It;
        if (!SalesStandActor || !SalesStandActor->TargetComp) continue;
        if (SalesStandActor->TargetComp->ComponentTags.Contains(*ProductName[index]))
        {
            if (SalesStandActor->CurrentProductCount == 0) {
                UE_LOG(LogTemp, Error, TEXT("SADASASDSAD"));
                index++;
                return true;
            }

        }
    }
    return false;


}
