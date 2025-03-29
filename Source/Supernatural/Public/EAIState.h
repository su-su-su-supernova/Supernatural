// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class  EAIState:uint8
{
	FindProduct         UMETA(DisplayName = "��ǰã��"),
	MoveToProduct       UMETA(DisplayName = "��ǰ�����̵�"),
	ProductFindFailed   UMETA(DisplayName = "��ǰã�����"),
	MoveToCounter       UMETA(DisplayName = "ī�����̵�"),
	ArriveAtCounter     UMETA(DisplayName = "ī���͵���"),
	LineUp             UMETA(DisplayName = "�ټ���")

};