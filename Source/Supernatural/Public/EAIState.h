// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class  EAIState:uint8
{
	FindProduct         UMETA(DisplayName = "상품찾기"),
	MoveToProduct       UMETA(DisplayName = "상품으로이동"),
	ProductFindFailed   UMETA(DisplayName = "상품찾기실패"),
	MoveToCounter       UMETA(DisplayName = "카운터이동"),
	ArriveAtCounter     UMETA(DisplayName = "카운터도착"),
	LineUp             UMETA(DisplayName = "줄서기")

};