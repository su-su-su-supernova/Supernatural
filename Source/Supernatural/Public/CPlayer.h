#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class SUPERNATURAL_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
#pragma region Camera
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* PlayerCamera;
#pragma endregion


#pragma region Collision
	// Main Board로부터 일정 거리 앞에 있는지 체크
	UPROPERTY(EditDefaultsOnly, Category = "ClickUI")
	bool bIsHitByMainBoard = false;

	// Stand로부터 일정 거리 앞에 있는지 체크
    UPROPERTY(EditDefaultsOnly, Category = "DP")
    bool bIsHitByStand = false;

	UFUNCTION()
	void OnOtherBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOtherEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
#pragma endregion


#pragma region IMC
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_PlayerInput;
#pragma endregion


#pragma region Motion Controller
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UMotionControllerComponent* LeftHand;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class USkeletalMeshComponent* SkeletalMeshLeftHand;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UMotionControllerComponent* RightHand;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class USkeletalMeshComponent* SkeletalMeshRightHand;
#pragma endregion


#pragma region Move
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_PlayerMove;

	void Move(const struct FInputActionValue& InValues);
#pragma endregion


#pragma region Turn
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_PlayerTurn;

	void Turn(const struct FInputActionValue& InValues);
#pragma endregion


    // Line Trace
    UPROPERTY(EditDefaultsOnly, Category = "Line Trace")
    bool bIsPerformingLineTrace = false;

	void PerformLineTrace(float InInteractionDistance);

    void SetInputMode();


#pragma region  Click UI
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_ClickUI;

	UPROPERTY(EditDefaultsOnly, Category = "ClickUI")
	bool bIsClickUIInputEntered = false;

	UPROPERTY(EditDefaultsOnly, Category = "ClickUI")
	bool bIsClickingUI = false;

	void ClickUIStart();
	void ClickUICompleted();


#pragma region Widget Interaction Component
	UPROPERTY(EditDefaultsOnly, Category = "WidgetInteraction")
	class UWidgetInteractionComponent* WidgetInteraction;

	UPROPERTY(EditAnywhere, Category = "WidgetInteraction")
	float InteractionDistanceWidget = 200.f;
#pragma endregion


#pragma endregion


#pragma region Grab Box
    UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_GrabBox;

	// Box 구별용 tag
	// 이렇게 FString 데이터를 const로 관리하면
	// 오타로 인한 에러를 방지할 수 있다
	const FName BOXTAG = FName("Box");

	// 박스를 잡고 있는 상태인지 체크
    UPROPERTY(EditDefaultsOnly, Category = "GrabBox")
    bool bIsGrabbingBox = false;

	// GrabBox input이 들어왔는지 체크
    UPROPERTY(EditDefaultsOnly, Category = "GrabBox")
    bool bIsGrabBoxInputEntered = false;

    UPROPERTY(EditAnywhere, Category = "GrabBox")
    float InteractionDistanceBox = 100.f;

	// 현재 들고 있는 박스
	UPROPERTY(EditAnywhere, Category = "GrabBox")
	class AProductBoxActor* Box;

	// 박스를 부착할 socket의 이름
	FName SocketAttachBox = TEXT("AttachBox");

	// 박스 안 물품의 정보
	FString ProductName;		
	int32 ProductCurrentStock; // 현재 박스 안에 있는 재고수

    // GrabBox input이 들어왔을 때 실행
    void GrabBoxInputStart();

    // 박스를 실제로 집을 때 할 행동
    void LiftBox();

    // GrabBox input이 끝났을 때 실행
    void GrabBoxInputCompleted();

    // 박스를 떨어뜨릴 때 할 행동
    void DropBox();
#pragma endregion


#pragma region Display Product
    UPROPERTY(EditDefaultsOnly, Category = "DP")
    class UInputAction* IA_DP;

    // 선반 구별용 tag
    const FName STANDTAG = FName("Stand");

    // Line Trace 탐색 거리
    UPROPERTY(EditDefaultsOnly, Category = "DP")
    float InteractionDistanceStand = 150;

    UPROPERTY(EditDefaultsOnly, Category = "DP")
    class ACLineTraceZone* LineTraceZone;

    // DP input이 들어왔는지 체크
    UPROPERTY(EditDefaultsOnly, Category = "DP")
    bool bIsDPInputEntered = false;

	// 선반에 Line Trace가 되었는지 체크
    UPROPERTY(EditDefaultsOnly, Category = "DP")
    bool bIsLineTraceToStand = false;

    // 현재 물품을 진열하고 있는가
    UPROPERTY(EditDefaultsOnly, Category = "DP")
    bool bIsDisplayingProduct = false;

	// 물품을 진열할 선반
	UPROPERTY(EditDefaultsOnly, Category = "DP")
	class AsalesStandActor* Stand;

    // DP input이 들어왔을 때 실행
    void DPStart();

    // 물품을 진열한다
    void DisplayProduct();

    // DP input이 끝났을 때 실행
    void DPCompleted();
#pragma endregion


#pragma region Calculate
    UPROPERTY(EditDefaultsOnly, Category = "Calculate")
    class UInputAction* IA_Calculate;

	// 카운터 구별용 tag
	const FName COUNTERTAG = FName("Counter");

    // 카드 구별용 tag
    const FName CARDTAG = FName("Card");

	// 상품 구별용 tag
	const FName PRODUCTTAG = FName("Product");

	bool bIsHitByCounter = false;
	bool bIsCalculateInputEntered = false;
	//bool bIsCalculating = false;

	void CalculateInputStarted();
	void CalculateInputCompleted();
	void Calculate(UStaticMeshComponent* InProduct);

	class ACCounter* Counter;

	class ASuperGameMode* SuperGameMode;

#pragma endregion

#pragma region Haptic
public:
	UPROPERTY(EditAnywhere, Category = "Haptic")
	class UHapticFeedbackEffect_Curve* HapticClick;
	UPROPERTY(EditAnywhere, Category = "Haptic")
	class UHapticFeedbackEffect_Curve* HapticAICollide;
#pragma endregion

};
