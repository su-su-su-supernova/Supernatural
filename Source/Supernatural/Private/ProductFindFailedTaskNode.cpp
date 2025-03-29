// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductFindFailedTaskNode.h"
#include "SuperAIController.h"
#include "NavigationSystem.h"
#include "AiCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SuperGameMode.h"


UProductFindFailedTaskNode::UProductFindFailedTaskNode()
{
    bNotifyTick = true;
}

EBTNodeResult::Type UProductFindFailedTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ASuperAIController* AiController = Cast<ASuperAIController>(OwnerComp.GetOwner());
        AiController->TargetLocation = getRandomLocation();
        return EBTNodeResult::InProgress;
}

void UProductFindFailedTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    ASuperAIController* AiController = Cast<ASuperAIController>(OwnerComp.GetOwner());
    ASuperGameMode* Gamemode = Cast<ASuperGameMode>(GetWorld()->GetAuthGameMode());
    if (!AiController) {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }
    if (Gamemode->GenerateGameModeTicketNumber() == AiController->TicketNumber) {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;

    }




    float AcceptableRadius = 100.0f;

    AiController->MoveToLocation(AiController->TargetLocation, 0);

    float Distance = FVector::Dist(AiController->TargetLocation, AiController->GetCharacter()->GetActorLocation());

    if (Distance <= AcceptableRadius) {

        AiController->TargetLocation = getRandomLocation();

        AiController->MoveToLocation(AiController->TargetLocation, 0);
    }
}

EBTNodeResult::Type UProductFindFailedTaskNode::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::AbortTask(OwnerComp, NodeMemory);
    return EBTNodeResult::Aborted;
}

FVector UProductFindFailedTaskNode::getRandomLocation()
{
    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    FVector RandomLocation = FVector::ZeroVector;
    FNavLocation NavLocation;
    FName TargetTag = FName(TEXT("SearchZone"));
    TArray<AActor*> TargetActor;

    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TargetTag, TargetActor);
    if (TargetActor.Num() > 0 && NavSys)
    {
        bool bFound = NavSys->GetRandomPointInNavigableRadius(
            TargetActor[0]->GetActorLocation(),
            TargetActor[0]->GetSimpleCollisionRadius(),
            NavLocation
        );

        if (bFound)
        {
            RandomLocation = NavLocation.Location;
        }
    }

    return RandomLocation;
}