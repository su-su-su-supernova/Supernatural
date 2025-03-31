// Fill out your copyright notice in the Description page of Project Settings.


#include "AiCharacter.h"
#include "SuperGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <SuperAIController.h>
#include "AiTartgetActor.h"
#include "salesStandActor.h"
#include "Components/BoxComponent.h"
#include "CCounter.h"

// Sets default values
AAiCharacter::AAiCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAiCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = 300;
	GetCharacterMovement()->bOrientRotationToMovement = false;


	if (auto ai = Cast<AAIController>(GetController()))
	{
		if (auto myAi = Cast<ASuperAIController>(ai))
		{
			for (int i = 0; i < 4; ++i)
			{
				/*UE_LOG(LogTemp, Warning,
					TEXT("Controller Name: %s\nPawn Name : %s\nProductName : %s"),
					*myAi->GetName(), *this->GetName(), *myAi->ProductName[i]);*/
			}
		}
	}
}

// Called every frame
void AAiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ASuperGameMode* g = Cast<ASuperGameMode>(GetWorld()->GetAuthGameMode());
	UE_LOG(LogTemp, Log, TEXT("%d"), g->GetIsCalculating());
	isBeginCounter = g->GetIsCalculating();

}

// Called to bind functionality to input
void AAiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAiCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	ASuperGameMode* g = Cast<ASuperGameMode>(GetWorld()->GetAuthGameMode());
	ASuperAIController* pc = Cast<ASuperAIController>(GetController());
	if (AsalesStandActor* salesStand = Cast<AsalesStandActor>(OtherActor)) {
		for (auto salesStandTag : salesStand->TargetComp->ComponentTags) {
			if (salesStandTag == (*pc->CurrentName)) {
				QProductData.Enqueue(salesStand->RemoveProduct());
				isBeginProduct = true;
				break;
			}
		}
	}
	if (ACCounter* Counter = Cast<ACCounter>(OtherActor)) {
		Counter->CustomerArrived(QProductData);
		int32 result;
		g->WaitingAIs.Dequeue(result);
		UE_LOG(LogTemp, Log, TEXT("asdasdsa"));
	}
	if (OtherActor->Tags.Contains(TEXT("End"))) {
		isBeginEnd = true;
	}
}

