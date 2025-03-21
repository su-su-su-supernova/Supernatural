#include "CPlayer.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "../../../../../../../Source/Runtime/HeadMountedDisplay/Public/MotionControllerComponent.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Components/WidgetInteractionComponent.h"

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

	/* Motion Controller */
	LeftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftHand"));
	LeftHand->SetTrackingMotionSource(TEXT("Left"));
	LeftHand->SetupAttachment(RootComponent);

	RightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightHand"));
	RightHand->SetTrackingMotionSource(TEXT("Right"));
	RightHand->SetupAttachment(RootComponent);

	/* Widget Interaction Component */
	WidgetInteraction = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteraction"));
	WidgetInteraction->SetupAttachment(RootComponent);
	WidgetInteraction->InteractionDistance = WidgetInteractionDistance;
	WidgetInteraction->InteractionSource = EWidgetInteractionSource::World;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 레이저가 UI를 감지하게 함
	PerformLineTrace();
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
	}

	/* Input Actions */
	auto inputSystem = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (inputSystem)
	{
		inputSystem->BindAction(IA_PlayerMove, ETriggerEvent::Triggered, this, &ACPlayer::Move);
		inputSystem->BindAction(IA_PlayerTurn, ETriggerEvent::Triggered, this, &ACPlayer::Turn);
		inputSystem->BindAction(IA_ClickUI, ETriggerEvent::Triggered, this,&ACPlayer::ClickUI);
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

void ACPlayer::PerformLineTrace()
{
	if(!WidgetInteraction) return;

	FVector startPos = WidgetInteraction->GetComponentLocation();
	FVector endPos = startPos + WidgetInteraction->GetForwardVector() * WidgetInteractionDistance;

	FHitResult hitResult;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	// Ray Trace
	if( GetWorld()->LineTraceSingleByChannel(hitResult, startPos, endPos, ECC_Visibility, params))
		WidgetInteraction->SetCustomHitResult(hitResult);
}

void ACPlayer::ClickUI()
{
	if (WidgetInteraction)
	{
		if (WidgetInteraction->IsOverInteractableWidget())
		{
			if (!bIsClickingUI)
			{
				WidgetInteraction->ReleasePointerKey(EKeys::OculusTouch_Right_A_Click);
				bIsClickingUI = true;
			}
			else
			{
				WidgetInteraction->ReleasePointerKey(EKeys::OculusTouch_Right_A_Click);
				bIsClickingUI = false;
			}
		}
	}
}

