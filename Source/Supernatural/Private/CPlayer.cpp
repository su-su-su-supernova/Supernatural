#include "CPlayer.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "../../../../../../../Source/Runtime/HeadMountedDisplay/Public/MotionControllerComponent.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Components/WidgetInteractionComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "MainBoardWidget.h"
#include "CComputer.h"
#include "ProductBoxActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "salesStandActor.h"
#include "CLineTraceZone.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Camera */
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamer"));
	PlayerCamera->SetupAttachment(RootComponent);
	PlayerCamera->SetRelativeLocation(FVector(0,0,95));


	/* Collision */
	GetCapsuleComponent()->SetCollisionProfileName(FName("Player"));
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACPlayer::OnOtherBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACPlayer::OnOtherEndOverlap);


	/* IMC */
	ConstructorHelpers::FObjectFinder<UInputMappingContext> tmpIMC(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/DYL/Inputs/IMC_PlayerInput.IMC_PlayerInput'"));
	if (tmpIMC.Succeeded()) IMC_PlayerInput = tmpIMC.Object;


	/* Input Actions*/
	ConstructorHelpers::FObjectFinder<UInputAction> tmpIAMove(TEXT("/Script/EnhancedInput.InputAction'/Game/DYL/Inputs/IA_PlayerMove.IA_PlayerMove'"));
	if(tmpIAMove.Succeeded()) IA_PlayerMove = tmpIAMove.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> tmpIATurn(TEXT("/Script/EnhancedInput.InputAction'/Game/DYL/Inputs/IA_PlayerTurn.IA_PlayerTurn'"));
	if (tmpIAMove.Succeeded()) IA_PlayerTurn = tmpIATurn.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> tmpIAClickUI(TEXT("/Script/EnhancedInput.InputAction'/Game/DYL/Inputs/IA_ClickUI.IA_ClickUI'"));
	if (tmpIAMove.Succeeded()) IA_ClickUI = tmpIAClickUI.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> tmpIAGrabBox(TEXT("/Script/EnhancedInput.InputAction'/Game/DYL/Inputs/IA_GrabBox.IA_GrabBox'"));
	if (tmpIAGrabBox.Succeeded()) IA_GrabBox = tmpIAGrabBox.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> tmpIADP(TEXT("/Script/EnhancedInput.InputAction'/Game/DYL/Inputs/IA_DP.IA_DP'"));
	if (tmpIAGrabBox.Succeeded()) IA_DP = tmpIADP.Object;


	/* Motion Controller - Left Hand */
	LeftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftHand"));
	LeftHand->SetTrackingMotionSource(TEXT("Left"));
	LeftHand->SetupAttachment(RootComponent);

	SkeletalMeshLeftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshLeftHand"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpLeftHand(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'"));
	if (tmpLeftHand.Succeeded())
		SkeletalMeshLeftHand->SetSkeletalMesh(tmpLeftHand.Object);

	SkeletalMeshLeftHand->SetupAttachment(LeftHand);

	SkeletalMeshLeftHand->SetRelativeRotation(FRotator(-85.000001, 0.000000, 269.999997));


	/* Motion Controller - Right Hand */
	RightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightHand"));
	RightHand->SetTrackingMotionSource(TEXT("Right"));
	RightHand->SetupAttachment(RootComponent);

	SkeletalMeshRightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshRightHand"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpRightHand(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'"));
	if (tmpRightHand.Succeeded()) SkeletalMeshRightHand->SetSkeletalMesh(tmpRightHand.Object);

	SkeletalMeshRightHand->SetupAttachment(RightHand);

	SkeletalMeshRightHand->SetRelativeRotation(FRotator(94.999999, 0.000011, 90.000010));


	/* Widget Interaction Component */
	WidgetInteraction = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteraction"));
	WidgetInteraction->SetupAttachment(RootComponent);
	WidgetInteraction->InteractionDistance = InteractionDistanceWidget;
	WidgetInteraction->InteractionSource = EWidgetInteractionSource::World;
	WidgetInteraction->TraceChannel = ECollisionChannel::ECC_Visibility;

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	auto pc = Cast<APlayerController>(GetController());
	if(pc)
	{
        UE_LOG(LogTemp, Error, TEXT(">>>>>> Input Mode : GameAndUI"));
		pc->SetInputMode(FInputModeGameAndUI());
	}

	//SetInputMode();
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Main Board�κ��� ���� �Ÿ� �տ� ������ Widget���� interaction üũ�� ���� Custom Ray Trace ����
	if(bIsHitByMainBoard)
		PerformLineTrace(InteractionDistanceWidget);

	// Left Trigger Slide�� ������ ������ Box���� interaction üũ�� ���� Custom Ray Trace ����
	if(bIsGrabBoxInputEntered)
		PerformLineTrace(InteractionDistanceBox);

	// Shelf�κ��� ���� �Ÿ� �տ� ������ Shelf���� interaction üũ�� ���� Custom Ray Trace ����
	if(bIsHitByStand)
		PerformLineTrace(InteractionDistanceShelf);
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
		inputSystem->BindAction(IA_ClickUI, ETriggerEvent::Started, this,&ACPlayer::ClickUIStart);
		inputSystem->BindAction(IA_ClickUI, ETriggerEvent::Completed, this, &ACPlayer::ClickUICompleted);
		inputSystem->BindAction(IA_GrabBox, ETriggerEvent::Started, this, &ACPlayer::GrabBoxInputStart);
		inputSystem->BindAction(IA_GrabBox, ETriggerEvent::Completed, this, &ACPlayer::GrabBoxInputCompleted);
		inputSystem->BindAction(IA_DP, ETriggerEvent::Started, this, &ACPlayer::DPStart);
		inputSystem->BindAction(IA_DP, ETriggerEvent::Completed, this, &ACPlayer::DPCompleted);
	}
}


#pragma region Collision
void ACPlayer::OnOtherBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACComputer>(OtherActor))
	{
		if (!bIsHitByMainBoard)
		{
			bIsHitByMainBoard = true;
			UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>>>>>>>>>>> Collide with Computer >>>>>>>>>>>>>>>>>>>"));
		}
		return;
    }

	if (Cast<ACLineTraceZone>(OtherActor))
	{
		if (!bIsHitByStand)
		{
			LineTraceZone = Cast<ACLineTraceZone>(OtherActor);
			bIsHitByStand = true;
			UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>>>>>>>>>>> Collide with Stand >>>>>>>>>>>>>>>>>>>"));
		}
		return;
	}
}

void ACPlayer::OnOtherEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ACComputer>(OtherActor))
	{
		UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>>>>>>>>>>> Collide End with Computer >>>>>>>>>>>>>>>>>>>"));
		bIsHitByMainBoard = false;
		return;
	}

	if (Cast<ACLineTraceZone>(OtherActor))
	{
		UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>>>>>>>>>>> Collide End with Stand >>>>>>>>>>>>>>>>>>>"));
		bIsHitByStand = false;
		return;
	}
	///////////////////
	isHitStand = true;
	///////////////////

}
#pragma endregion


#pragma region Move
void ACPlayer::Move(const FInputActionValue& InValues)
{
	FVector2D Scale = InValues.Get<FVector2D>();
	FVector dir = PlayerCamera->GetForwardVector() * Scale.X + PlayerCamera->GetRightVector() * Scale.Y;
	AddMovementInput(dir);
}
#pragma endregion


#pragma region Turn
void ACPlayer::Turn(const FInputActionValue& InValues)
{
	FVector2d scale = InValues.Get<FVector2d>();
	AddControllerPitchInput(-scale.Y);
	AddControllerYawInput(scale.X);
}
#pragma endregion


void ACPlayer::PerformLineTrace(float InInteractionDistance)
{
	FVector startPos = RightHand->GetComponentLocation();
	FVector endPos = startPos + RightHand->GetForwardVector() * InInteractionDistance;
	FString interactionType = InInteractionDistance == InteractionDistanceWidget ? TEXT("Widget") : TEXT("Box");

	// UE_LOG(LogTemp, Warning, TEXT("[Interaction with %s] / startPos : %f / endPos : %f"), *interactionType, startPos.Size(), endPos.Size());

	FHitResult hitResult;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(LineTraceZone);

	// Line Trace�� �����ϴ� ��ü�� ���� ���� �ٸ���
	FColor drawColor = InInteractionDistance == InteractionDistanceWidget ? FColor::Magenta : FColor::Cyan;
	drawColor = InInteractionDistance == InteractionDistanceShelf ? FColor::Orange : drawColor;

	DrawDebugLine(GetWorld(), startPos, endPos, drawColor, false, -1, 0, 1);

	// Ray Trace
	if (GetWorld()->LineTraceSingleByChannel(hitResult, startPos, endPos, ECC_Visibility, params))
	{
		endPos = hitResult.ImpactPoint;

		FString hitActor = hitResult.GetActor()->GetActorNameOrLabel();
		//UE_LOG(LogTemp, Warning, TEXT(">>>>> Hit at %s"), *hitActor);

		/* Click UI */
		if (InInteractionDistance == InteractionDistanceWidget)
		{
			// Widget Interaction�� Custom ray tracing ��� ����
			WidgetInteraction->SetCustomHitResult(hitResult);
			return;
		}

		/* Grab Box */
		if (InInteractionDistance == InteractionDistanceBox && hitResult.GetActor()->ActorHasTag(BOXTAG))
		{
			// hit�� box�� ����Ѵ�
			Box = Cast<AProductBoxActor>(hitResult.GetActor());

			// Box �� Symulate Physics�� ���ش�
			Box->BoxPhysicsOnOff(false);

			// Box�� ���ø���
			if(!bIsGrabbingBox)
				LiftBox();
			return;
		}

		/* Display Product */
		if (InInteractionDistance == InteractionDistanceShelf && hitResult.GetActor()->ActorHasTag(SHELFTAG) && bIsDPInputEntered)
		{
			UE_LOG(LogTemp, Warning, TEXT(">>>>> Hit at %s"), *hitActor);

			// hit�� stand�� ����Ѵ�
			Stand = Cast<AsalesStandActor>(hitResult.GetActor());

			isHitStand = true;

			// ��ǰ�� �����Ѵ�
			DisplayProduct();
		}
	}
}


void ACPlayer::SetInputMode()
{
	auto* pc = GetWorld()->GetFirstPlayerController();
	if (!pc) return;

	// Line Trace�� ���� ���̰� Widget�� ��ȣ�ۿ� ���� �� UI �Է����θ� �Է��� �ް� ��
	if (bIsPerformingLineTrace && WidgetInteraction)pc->SetInputMode(FInputModeUIOnly());
	else pc->SetInputMode(FInputModeGameOnly());
}


#pragma region Click UI
void ACPlayer::ClickUIStart()
{
	if(!bIsClickUIInputEntered) bIsClickUIInputEntered = true;

	if (bIsClickUIInputEntered && WidgetInteraction)
	{
		UE_LOG(LogTemp, Error, TEXT(">>> WidgetInteraction Success!!!"));
		if (WidgetInteraction->IsOverInteractableWidget())
		{
			UE_LOG(LogTemp, Error, TEXT(">>> Widget Interactable widget SUCCESS !!!!!!!!!!!"));
			/*if (!bIsClickingUI)
			{
				WidgetInteraction->PressPointerKey(EKeys::LeftMouseButton);
				bIsClickingUI = true;
				UE_LOG(LogTemp, Warning, TEXT(">>> Activate Click A - bIsClickingUI : %d"), bIsClickingUI);
			}
			else
			{
				WidgetInteraction->ReleasePointerKey(EKeys::LeftMouseButton);
				bIsClickingUI = false;
				UE_LOG(LogTemp, Warning, TEXT(">>> Deactivate Click A - bIsClickingUI : %d"), bIsClickingUI);
			}*/
			WidgetInteraction->PressPointerKey(EKeys::LeftMouseButton);
			// bIsClickingUI = true;
			UE_LOG(LogTemp, Warning, TEXT(">>> Activate Click A - bIsClickingUI : %d"), bIsClickingUI);
		}
	}
	/////////////////////////////////////////////////
	if (isHitStand) {
		if (!Stand)return;
		Stand->SetMeshesForProductNumber("Coke");
	}
	/////////////////////////////////////////////////

}

void ACPlayer::ClickUICompleted()
{
	bIsClickUIInputEntered = false;
	//SetInputMode();

	WidgetInteraction->ReleasePointerKey(EKeys::LeftMouseButton);
	// bIsClickingUI = false;
	UE_LOG(LogTemp, Warning, TEXT(">>> Deactivate Click A - bIsClickingUI : %d"), bIsClickingUI);
}

#pragma endregion


#pragma region Grab Box
void ACPlayer::GrabBoxInputStart()
{
	// GrabBox input�� ���۵Ǿ��ٰ� ����Ѵ�
	bIsGrabBoxInputEntered = true;
	UE_LOG(LogTemp, Error, TEXT(">>>>> Grab Box Input Start"));
}

void ACPlayer::LiftBox()
{
    UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> Lift Box <<<<<<<<<<"));

	// Box�� AttachBox socket�� Attach�Ѵ�
	FString rslt = SkeletalMeshLeftHand->DoesSocketExist(SocketAttachBox) ? TEXT("True") : TEXT("False");
	//FString rslt = LeftHand->GetAttachSocketName().Compare(SocketAttachBox) ? TEXT("True") : TEXT("False");

	UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>> Does socket exist? %s"), *rslt);

	if (SkeletalMeshLeftHand->DoesSocketExist(SocketAttachBox))
	{
		if (Box->AttachToComponent(SkeletalMeshLeftHand, FAttachmentTransformRules::KeepWorldTransform, SocketAttachBox))
		{
			// Box�� ��� �ִٰ� ����Ѵ�
			bIsGrabbingBox = true;

			UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>> ATTACH BOX SUCCESS <<<<<<<<<<"));

			// Box�� ������ �����´�
			ProductName = Box->ProductNameGetter().ToString();
			ProductCostPrice = Box->CostPriceGetter();
			ProductOrderStock = Box->OrderStockGetter();

			UE_LOG(LogTemp, Warning, TEXT("[Product Info] Product Location : %s / Product Name : %s / Product Cost Price : %d / Product Order Stock : %d"), *(Box->GetActorLocation().ToString()), *ProductName, ProductCostPrice, ProductOrderStock);

		}
	}
}

void ACPlayer::GrabBoxInputCompleted()
{
	// GrabBox input�� �����ٰ� ����Ѵ�
	bIsGrabBoxInputEntered = false;
	UE_LOG(LogTemp, Error, TEXT(">>>>> Grab Box Input Completed"));

	// Box�� ��� �ִٸ� Box�� ����߸���
	if(Box)
		DropBox();
}

void ACPlayer::DropBox()
{
	UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> Drop Box <<<<<<<<<<"));

	// Box�� ��� ���� �ʴٰ� ����Ѵ�
	if(bIsGrabbingBox) bIsGrabbingBox = false;

	// Box�� AttachBox socket���κ��� Detach�Ѵ�
	Box->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>> DETACH BOX SUCCESS <<<<<<<<<<"));

	// Box �� Symulate Physics�� ���ش�
	Box->BoxPhysicsOnOff(true);
}
#pragma endregion


#pragma region Display Product
void ACPlayer::DPStart()
{
	// input�� �������� ����Ѵ�
	bIsDPInputEntered = true;
	UE_LOG(LogTemp, Error, TEXT(">>>>> DP Input Start"));
}

void ACPlayer::DisplayProduct()
{
	// �ڽ��� ��� ���� �ʰų�
	// ���ݿ� �ִ�� ��ġ�� �� ���� ��ŭ ��ġ�ߴٸ� ������
	if( !bIsGrabbingBox || (CurDP == ProductOrderStock) ) return;

	UE_LOG(LogTemp, Error, TEXT(">>>>> Display Product Start <<<<<"));
	// ���ݿ� ��ǰ�� �����ϰ�
	// Stand->

	// ���� ������ ��ǰ�� ������ 1 ������Ų��
	CurDP++;
}

void ACPlayer::DPCompleted()
{
	// DP�� ��ǰ�� ������ �ʱ�ȭ�Ѵ�
	CurDP = 0;

	// input�� �������� ����Ѵ�
	bIsDPInputEntered = false;

	UE_LOG(LogTemp, Error, TEXT(">>>>> DP Input Complete"));
}

#pragma endregion
