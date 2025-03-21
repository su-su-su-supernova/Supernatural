#include "CPlayer.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Camera */
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamer"));
	PlayerCamera->SetupAttachment(RootComponent);
	PlayerCamera->SetRelativeLocation(FVector(0,0,95));

	/* IMC */
	ConstructorHelpers::FObjectFinder<UInputMappingContext> tmpIMC(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/DYL/Inputs/IMC_PlayerInput.IMC_PlayerInput'"));
	if (tmpIMC.Succeeded()) IMC_PlayerInput = tmpIMC.Object;

	/* Input Actions*/
	ConstructorHelpers::FObjectFinder<UInputAction> tmpIAMove(TEXT("/Script/EnhancedInput.InputAction'/Game/DYL/Inputs/IA_PlayerMove.IA_PlayerMove'"));
	if(tmpIAMove.Succeeded()) IA_PlayerMove = tmpIAMove.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> tmpIATurn(TEXT("/Script/EnhancedInput.InputAction'/Game/DYL/Inputs/IA_PlayerTurn.IA_PlayerTurn'"));
	if (tmpIAMove.Succeeded()) IA_PlayerTurn = tmpIATurn.Object;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// IMC
	APlayerController* pc = Cast<APlayerController>(GetController());
	if (pc)
	{
		auto localPlayer = pc->GetLocalPlayer();
		auto ss = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);
		if (ss)
			ss->AddMappingContext(IMC_PlayerInput, 1);

		UE_LOG(LogTemp, Warning, TEXT(">> IMC Add Success"));
	}

	/* Input Actions */
	auto inputSystem = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (inputSystem)
	{
		inputSystem->BindAction(IA_PlayerMove, ETriggerEvent::Triggered, this, &ACPlayer::Move);
		inputSystem->BindAction(IA_PlayerTurn, ETriggerEvent::Triggered, this, &ACPlayer::Turn);
		UE_LOG(LogTemp, Warning, TEXT(">> IA_Move Add Success"));
	}
}

void ACPlayer::Move(const FInputActionValue& InValues)
{
	FVector2D Scale = InValues.Get<FVector2D>();
	FVector dir = PlayerCamera->GetForwardVector() * Scale.X + PlayerCamera->GetRightVector() * Scale.Y;
	AddMovementInput(dir);
}

void ACPlayer::Turn(const FInputActionValue& InValues)
{
	FVector2d scale = InValues.Get<FVector2d>();
	AddControllerPitchInput(-scale.Y);
	AddControllerYawInput(scale.X);
}

