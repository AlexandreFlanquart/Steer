// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <MyGameInstance.h>
#include "MyActor.generated.h"


UCLASS()
class STEER_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	FVector way1[5];
	int point;
	APlayerController* controller;
	FVector acceleration;
	float max_force;
	int sens;
	float mass;
	//FVector position;
	FVector velocity;

	float max_speed;

	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Move(float DeltaTime);
	void Seek(FVector position, FVector target, float DeltaTime);
	void Flee(FVector position, FVector target, float DeltaTime);
	void Pursuit(FVector position, FVector target, float DeltaTime);
	void Arrival(FVector position, FVector target, float DeltaTime);
	void Evade(FVector position, FVector target, float DeltaTime);

};
