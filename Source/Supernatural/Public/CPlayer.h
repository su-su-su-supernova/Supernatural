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

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
public:
	/* Camera */
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* PlayerCamera;

	/* Inputs */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_PlayerInput;

	// Move
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_PlayerMove;
	void Move(const struct FInputActionValue& InValues);

	// Turn
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_PlayerTurn;
	void Turn(const struct FInputActionValue& InValues);
};
