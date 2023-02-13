// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UENUM()
enum  Mode {
	SEEK,
	FLEE,
	ARRIVAL,
	EVADE,
	PURSUIT,
	WAY1,
	WAY2,
	CIRCUIT
};


UCLASS()
class STEER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
		Mode mode;
		UMyGameInstance();
};
