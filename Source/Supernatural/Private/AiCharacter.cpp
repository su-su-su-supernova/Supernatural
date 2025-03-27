// Fill out your copyright notice in the Description page of Project Settings.


#include "AiCharacter.h"
#include "SuperGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <SuperAIController.h>

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
	GetCharacterMovement()->MaxWalkSpeed = 600;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	
	if (auto ai = Cast<AAIController>(GetController()))
	{
		if (auto myAi = Cast<ASuperAIController>(ai))
		{
			for (int i = 0; i < 4; ++i)
			{
				UE_LOG(LogTemp, Warning,
					TEXT("Controller Name: %s\nPawn Name : %s\nProductName : %s"),
						*myAi->GetName(), *this->GetName(), *myAi->ProductName[i]);
			}
		}
	}
}

// Called every frame
void AAiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

