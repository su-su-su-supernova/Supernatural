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
	// Main Board�κ��� ���� �Ÿ� �տ� �ִ��� üũ
	UPROPERTY(EditDefaultsOnly, Category = "ClickUI")
	bool bIsHitByMainBoard = false;

	// Stand�κ��� ���� �Ÿ� �տ� �ִ��� üũ
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


    // Custom Line Trace
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

	// Box ������ tag
	// �̷��� FString �����͸� const�� �����ϸ�
	// ��Ÿ�� ���� ������ ������ �� �ִ�
	const FName BOXTAG = FName("Box");

	// �ڽ��� ��� �ִ� �������� üũ
    UPROPERTY(EditDefaultsOnly, Category = "GrabBox")
    bool bIsGrabbingBox = false;

	// GrabBox input�� ���Դ��� üũ
    UPROPERTY(EditDefaultsOnly, Category = "GrabBox")
    bool bIsGrabBoxInputEntered = false;

    UPROPERTY(EditAnywhere, Category = "GrabBox")
    float InteractionDistanceBox = 30.f;

	// ���� ��� �ִ� �ڽ�
	UPROPERTY(EditAnywhere, Category = "GrabBox")
	class AProductBoxActor* Box;

	// �ڽ��� ������ socket�� �̸�
	FName SocketAttachBox = TEXT("AttachBox");

	// �ڽ� �� ��ǰ�� ����
	FString ProductName;
	int32 ProductCostPrice;
	int32 ProductOrderStock;

    // GrabBox input�� ������ �� ����
    void GrabBoxInputStart();

    // �ڽ��� ������ ���� �� �� �ൿ
    void LiftBox();

    // GrabBox input�� ������ �� ����
    void GrabBoxInputCompleted();

    // �ڽ��� ����߸� �� �� �ൿ
    void DropBox();
#pragma endregion


#pragma region Display Product
    UPROPERTY(EditDefaultsOnly, Category = "DP")
    class UInputAction* IA_DP;

    // ���� ������ tag
    const FName STANDTAG = FName("Stand");

    // Line Trace Ž�� �Ÿ�
    UPROPERTY(EditDefaultsOnly, Category = "DP")
    float InteractionDistanceStand = 100.f;

    UPROPERTY(EditDefaultsOnly, Category = "DP")
    class ACLineTraceZone* LineTraceZone;

    // DP input�� ���Դ��� üũ
    UPROPERTY(EditDefaultsOnly, Category = "DP")
    bool bIsDPInputEntered = false;

	// ���ݿ� Line Trace�� �Ǿ����� üũ
    UPROPERTY(EditDefaultsOnly, Category = "DP")
    bool bIsLineTraceToStand = false;

    // ���� ��ǰ�� �����ϰ� �ִ°�
    UPROPERTY(EditDefaultsOnly, Category = "DP")
    bool bIsDisplayingProduct;

	// ��ǰ�� ������ ����
	UPROPERTY(EditDefaultsOnly, Category = "DP")
	class AsalesStandActor* Stand;

    // ���� �� ���� ��ǰ�� �����Ǿ��°�
    int32 CurDP = 0;

    // DP input�� ������ �� ����
    void DPStart();

    // ��ǰ�� �����Ѵ�
    void DisplayProduct();

    // DP input�� ������ �� ����
    void DPCompleted();

#pragma endregion
	/////////////////****//////
	bool isHitStand=false;
};
