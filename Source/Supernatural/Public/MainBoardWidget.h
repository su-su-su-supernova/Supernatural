// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProductInfoWidget.h"
#include "MainBoardWidget.generated.h"

/**
 *
 */
UCLASS()
class SUPERNATURAL_API UMainBoardWidget : public UUserWidget
{
	GENERATED_BODY()
	UMainBoardWidget(const FObjectInitializer& ObjectInitializer);


public:
	virtual void NativeConstruct() override;





public:
	class UProductInfoWidget* ProductInfoWidget;

		UPROPERTY(meta = (BindWidget))
	class UWrapBox* WrapBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UProductInfoWidget> ProductInfoWidgetTool;


	UPROPERTY(meta = (BindWidget))
	class UButton* purchaseButton;
	   UFUNCTION()
    void OnButtonClicked();


};
