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

    // �迭 ũ�Ⱑ 4�� �����Ǿ� �����Ƿ�, �ִ� 4���� ����
    TArray<FString> ProductNames; // FString���� ����
    for (int i = 0; i < 4 && AvailableIndices.Num() > 0; i++) {
        int32 RandomIndex = FMath::RandRange(0, AvailableIndices.Num() - 1); // ���� �ε��� �� �ϳ� ����
        int32 SelectedIndex = AvailableIndices[RandomIndex]; // ���õ� �ε���
        ProductNames.Add(GameMode->GetProductDataByIndex(SelectedIndex)->ProductName); // ��ǰ �̸� �Ҵ� (FString ����)
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
    // �±� �˻�: ProductName 4���� ���� ���� �� ������ Ȯ��
    TArray<FString> MatchedTags; // ��ġ�ϴ� �±׸� ������ �迭
    for (const FString& Name : ProductNames) {
        // ���忡�� �ش� �̸��� ��ġ�ϴ� �±׸� ���� ���͸� ã��
        for (TActorIterator<AActor> It(GetWorld()); It; ++It) {
            AActor* Actor = *It;
            for (const FName& Tag : Actor->Tags) {
                if (Tag.ToString() == Name) { // FName�� FString���� ��ȯ�� ��
                    MatchedTags.Add(Name); // ��ġ�ϸ� �߰�
                    break; // �ش� �̸��� ���� �� �̻� �˻��� �ʿ� ����
                }
            }
            // �̹� ã������ ���� �̸����� �Ѿ
            if (MatchedTags.Contains(Name)) {
                break;
            }
        }
    }

    // ��� Ȯ�� (������)
    for (const FString& MatchedTag : MatchedTags) {
        ProductName.Add(MatchedTag);
    }

}

