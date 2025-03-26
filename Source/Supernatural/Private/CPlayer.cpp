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
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h"

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
	WidgetInteraction->SetupAttachment(RightHand);
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
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Main Board로부터 일정 거리 앞에 있으면 Widget과의 interaction 체크를 위해 Custom Ray Trace 실행
	if (bIsHitByMainBoard && !bIsGrabbingBox)
		PerformLineTrace(InteractionDistanceWidget);

	// Left Trigger Slide를 누르고 있으면 Box와의 interaction 체크를 위해 Custom Ray Trace 실행
	if (bIsGrabBoxInputEntered)
		PerformLineTrace(InteractionDistanceBox);

	// Shelf로부터 일정 거리 앞에 있으면 Shelf와의 interaction 체크를 위해 Custom Ray Trace 실행
	if (bIsHitByStand)
		PerformLineTrace(InteractionDistanceStand);
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
	if (Cast<ACLineTraceZone>(OtherActor))
	{
		LineTraceZone = Cast<ACLineTraceZone>(OtherActor);
		if (OtherActor->ActorHasTag(STANDTAG))
		{
			if (!bIsHitByStand)
			{
				bIsHitByStand = true;
				UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>>>>>>>>>>> Collide with Stand >>>>>>>>>>>>>>>>>>>"));
			}
		}
		else
		{
			if (!bIsHitByMainBoard)
            {
                bIsHitByMainBoard = true;
                UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>>>>>>>>>>> Collide with Computer >>>>>>>>>>>>>>>>>>>"));
				
            }
		}
	}
}

void ACPlayer::OnOtherEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ACLineTraceZone>(OtherActor))
	{
		if (OtherActor->ActorHasTag(STANDTAG))
		{
			UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>>>>>>>>>>> Collide End with Stand >>>>>>>>>>>>>>>>>>>"));
			bIsHitByStand = false;
		}
		else 
		{
			UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>>>>>>>>>>> Collide End with Computer >>>>>>>>>>>>>>>>>>>"));
			bIsHitByMainBoard = false;
		}
	}
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
	AddControllerPitchInput(scale.Y);
	AddControllerYawInput(scale.X);
}
#pragma endregion


void ACPlayer::PerformLineTrace(float InInteractionDistance)
{
	FVector startPos, endPos;
	startPos = RightHand->GetComponentLocation();
	endPos = startPos + RightHand->GetForwardVector() * InInteractionDistance;

	FHitResult hitResult;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(LineTraceZone);
	if (bIsGrabbingBox) params.AddIgnoredActor(Box);

	// Line Trace를 실행하는 주체에 따라 색상 다르게
	FColor drawColor;
	if(InInteractionDistance == InteractionDistanceWidget) drawColor = FColor::Magenta;
	else if(InInteractionDistance == InteractionDistanceStand) drawColor = FColor::Orange;
	else drawColor = FColor::Cyan;

	DrawDebugLine(GetWorld(), startPos, endPos, drawColor, false, -1, 0, 1);

	// Ray Trace
	if (GetWorld()->LineTraceSingleByChannel(hitResult, startPos, endPos, ECC_Visibility, params))
	{
		FString hitActor = hitResult.GetActor()->GetActorNameOrLabel();
		//UE_LOG(LogTemp, Warning, TEXT(">>>>> Hit at %s"), *hitActor);
		

		/* Display Product */
		if (hitResult.GetActor()->ActorHasTag(STANDTAG) && bIsGrabbingBox)
		{
			//UE_LOG(LogTemp, Warning, TEXT(">>>>> Hit at %s"), *hitActor);

			// hit된 stand를 명시한다
			Stand = Cast<AsalesStandActor>(hitResult.GetActor());

			// 선반에 Line Trace가 되어 있다고 명시한다
			bIsLineTraceToStand = true;
		}
		else bIsLineTraceToStand = false;


		/* Grab Box */
		if (bIsGrabBoxInputEntered && hitResult.GetActor()->ActorHasTag(BOXTAG) && !bIsGrabbingBox)
		{
			// hit된 box를 명시한다
			Box = Cast<AProductBoxActor>(hitResult.GetActor());

			// Box를 들어올린다
			if (!bIsGrabbingBox)
				LiftBox();
		}


		/* Click UI */
		if (bIsClickUIInputEntered && bIsHitByMainBoard && !bIsGrabbingBox)
		{
            //UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> hitResult : %s"), *(hitResult.ToString()));
			// Widget Interaction에 Custom ray tracing 결과 전달
			WidgetInteraction->SetCustomHitResult(hitResult);
			//return;
		}

		//bIsLineTraceToStand = false;
	}
}


void ACPlayer::SetInputMode()
{
	auto* pc = GetWorld()->GetFirstPlayerController();
	if (!pc) return;

	// Line Trace를 진행 중이고 Widget과 상호작용 중일 땐 UI 입력으로만 입력을 받게 함
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
		UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>>>>>>>>>>>>> IsOverInteractableWidget : %d"), WidgetInteraction->IsOverInteractableWidget());

		if (WidgetInteraction->IsOverInteractableWidget())
		{
			UE_LOG(LogTemp, Error, TEXT(">>> Widget Interactable widget SUCCESS !!!!!!!!!!!"));
			WidgetInteraction->PressPointerKey(EKeys::LeftMouseButton);
			bIsClickingUI = true;
			UE_LOG(LogTemp, Warning, TEXT(">>> Activate Click A - bIsClickingUI : %d"), bIsClickingUI);
		}
	}
}

void ACPlayer::ClickUICompleted()
{
	bIsClickUIInputEntered = false;

	WidgetInteraction->ReleasePointerKey(EKeys::LeftMouseButton);
	bIsClickingUI = false;
	UE_LOG(LogTemp, Warning, TEXT(">>> Deactivate Click A - bIsClickingUI : %d"), bIsClickingUI);
}

#pragma endregion


#pragma region Grab Box
void ACPlayer::GrabBoxInputStart()
{
	// GrabBox input이 시작되었다고 명시한다
	bIsGrabBoxInputEntered = true;
	UE_LOG(LogTemp, Error, TEXT(">>>>> Grab Box Input Start"));
}

void ACPlayer::LiftBox()
{
    UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> Lift Box <<<<<<<<<<"));

	// socket이 있다면
	if (SkeletalMeshLeftHand->DoesSocketExist(SocketAttachBox))
	{
		// Box를 잡고 있다고 명시한다
		bIsGrabbingBox = true;

		// Box의 Symulate Physics를 꺼준다
		Box->BoxPhysicsOnOff(false);

		// Box의 충돌 처리를 꺼준다
		Box->FindComponentByClass<UBoxComponent>()->SetCollisionProfileName(TEXT("NoCollision"));

		// Box의 위치를 socket 위치로 보정한다
		FVector socketLocation = RightHand->GetSocketLocation(SocketAttachBox);
		Box->SetActorLocation(socketLocation);

		if (Box->AttachToComponent(SkeletalMeshLeftHand, FAttachmentTransformRules::KeepWorldTransform, SocketAttachBox))
		{
			UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>> ATTACH BOX SUCCESS <<<<<<<<<<"));

			// Box의 정보를 가져온다
			ProductName = Box->ProductNameGetter().ToString();
			ProductCurrentStock = Box->CurrentStockGetter();

			UE_LOG(LogTemp, Warning, TEXT("[Product Info] Product Location : %s / Product Name : %s / Product Current Stock : %d"), *(Box->GetActorLocation().ToString()), *ProductName, ProductCurrentStock);
		}
	}
}

void ACPlayer::GrabBoxInputCompleted()
{
	// 물체를 잡고 있지 않다면 아무 처리하지 않는다
	if(bIsGrabbingBox == false) return;

	// GrabBox input이 끝났다고 명시한다
	bIsGrabBoxInputEntered = false;

	// Box를 떨어뜨린다
	DropBox();
}

void ACPlayer::DropBox()
{
	UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> Drop Box <<<<<<<<<<"));

	// Box를 잡고 있지 않다고 명시한다
	bIsGrabbingBox = false;

	// Box를 AttachBox socket으로부터 Detach한다
	Box->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>> DETACH BOX SUCCESS <<<<<<<<<<"));

	// Box 의 Symulate Physics를 켜준다
	Box->BoxPhysicsOnOff(true);

	// Box의 충돌 처리를 켜준다
	Box->FindComponentByClass<UBoxComponent>()->SetCollisionProfileName(TEXT("Box"));

	UE_LOG(LogTemp, Warning, TEXT("[DROP BOX] Product Location : %s / Product Name : %s / Product Current Stock : %d"), *(Box->GetActorLocation().ToString()), *ProductName, ProductCurrentStock);

	// Box를 null로 만들어준다
	Box = nullptr;
}
#pragma endregion


#pragma region Display Product
void ACPlayer::DPStart()
{
	// input이 들어왔음을 명시한다
	bIsDPInputEntered = true;
	UE_LOG(LogTemp, Error, TEXT(">>>>> DP Input Start"));

	// 선반에 Line Trace가 되었다면 Display를 진행해라
	if (bIsLineTraceToStand) DisplayProduct();
}

void ACPlayer::DisplayProduct()
{
	//UE_LOG(LogTemp, Error, TEXT("bIsGrabbingBox : %d / ProductCurrentStock : %d"), bIsGrabbingBox, ProductCurrentStock);
	
	// 박스를 들고 있지 않거나
	// 선반에 최대로 배치할 수 있을 만큼 배치했다면 끝낸다
	/*if( !bIsGrabbingBox || ProductCurrentStock == 0)
	{
		return;
	}*/

	if( !bIsGrabbingBox ) return;
	if (ProductCurrentStock == 0)
	{
		Box->SetCurrentStock(0);
		return;
	}

	UE_LOG(LogTemp, Error, TEXT(">>>>> Display Product Start <<<<<"));

	if (!Stand || ProductName.IsEmpty()) return;
	UE_LOG(LogTemp, Error, TEXT("Product Name : %s"), *ProductName);
	if (!Stand->SetMeshesForProductNumber("Tea"))
	{
		// 현재 Box에 들어 있는 물품 수를 1 감소시킨다
		Box->SetCurrentStock(ProductCurrentStock--);
	}

}

void ACPlayer::DPCompleted()
{
	// input이 끝났음을 명시한다
	bIsDPInputEntered = false;

	UE_LOG(LogTemp, Error, TEXT(">>>>> DP Input Complete"));
}

#pragma endregion
