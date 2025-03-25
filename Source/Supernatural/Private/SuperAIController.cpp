// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperAIController.h"
#include "Kismet/GameplayStatics.h"
#include "AiCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ASuperAIController::ASuperAIController()
{

	ConstructorHelpers::FObjectFinder<UBehaviorTree> AIBehavior(TEXT("/Game/HWL/AI/BT_AI.BT_AI"));
	if (AIBehavior.Succeeded())AIBehaviorTree = AIBehavior.Object;


}

void ASuperAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(AIBehaviorTree);
	GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 200;
	GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = true;
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

}

void ASuperAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	GetBlackboardComponent()->SetValueAsVector(TEXT("DefaultLocation"), GetPawn()->GetActorLocation());
	GetPawn()->bUseControllerRotationYaw = false;
	FindActor(PlayerPawn);
}

void ASuperAIController::FindActor(APawn* PlayerPawn)
{
	if (LineOfSightTo(PlayerPawn)) {
		SetFocus(PlayerPawn);
		GetPawn()->bUseControllerRotationYaw = true;
	}
	else {
		ClearFocus(EAIFocusPriority::Gameplay);
	}
	MoveToActor(PlayerPawn, 10);

}
