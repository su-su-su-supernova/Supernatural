// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperAIController.h"
#include "Kismet/GameplayStatics.h"
#include "AiCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BehaviorTree.h"

ASuperAIController::ASuperAIController()
{

	ConstructorHelpers::FObjectFinder<UBehaviorTree> AIBehavior(TEXT("/Game/HWL/AI/BT_AI.BT_AI"));
	if (AIBehavior.Succeeded())AIBehaviorTree = AIBehavior.Object;


}

void ASuperAIController::BeginPlay()
{
	Super::BeginPlay();
	GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 200;
	GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = true;
	RunBehaviorTree(AIBehaviorTree);
}

void ASuperAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

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
