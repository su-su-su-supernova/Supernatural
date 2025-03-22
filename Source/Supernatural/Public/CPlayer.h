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
	UPROPERTY(EditDefaultsOnly, Category = "ClickUI")
	bool bIsHitWithMainBoard = false;

	UFUNCTION()
	void OnOtherBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnMainBoardEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
#pragma endregion


#pragma region IMC
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_PlayerInput;
#pragma endregion


#pragma region Motion Controller
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UMotionControllerComponent* LeftHand;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UMotionControllerComponent* RightHand;
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

void CustomRayTrace(float InInteractionDistance);

#pragma region  Click UI
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_ClickUI;

	UPROPERTY(EditDefaultsOnly, Category = "ClickUI")
	bool bIsClickingUI = false;
	
	void ClickUI();


#pragma region Widget Interaction Component
	UPROPERTY(EditDefaultsOnly, Category = "WidgetInteraction")
	class UWidgetInteractionComponent* WidgetInteraction;

	UPROPERTY(EditAnywhere, Category = "WidgetInteraction")
	float WidgetInteractionDistance = 200.f;
#pragma endregion


#pragma endregion


#pragma region Grab Box
	// 박스를 잡고 있는 상태인지 체크
    UPROPERTY(EditDefaultsOnly, Category = "GrabBox")
    bool bIsGrabbingBox = false;

	// GrabBox input이 들어왔는지 체크
    UPROPERTY(EditDefaultsOnly, Category = "GrabBox")
    bool bIsIAGrabBoxEntered = false;

    UPROPERTY(EditAnywhere, Category = "GrabBox")
    float BoxInteractionDistance = 1.f;

	// 현재 들고 있는 박스의 정보
	UPROPERTY(EditAnywhere, Category = "GrabBox")
	class AProductBoxActor* Box;

    // GrabBox input이 들어왔을 때 실행
    void GrabBoxEnterStart();

    // 박스를 실제로 집을 때 할 행동
    void LiftBox();

    // GrabBox input이 끝났을 때 실행
    void GrabBoxEnterEnd();

    // 박스를 떨어뜨릴 때 할 행동
    void DropBox();
#pragma endregion
};
