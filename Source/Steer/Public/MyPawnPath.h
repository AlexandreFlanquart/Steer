// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <MyGameInstance.h>
#include <MyNode.h>
#include <Graph.h>
#include "MyPawnPath.generated.h"


using namespace std;

UCLASS()
class STEER_API AMyPawnPath : public APawn
{
	GENERATED_BODY()

public:
	UMyGameInstance* GI;
	bool m;

	Graph graph;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AMyNode*> listNodes = TArray<AMyNode*>(); // to touch
	vector<AMyNode*> path; // path to do
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMyNode* start;

	FVector acceleration;
	FVector velocity;
	float mass;
	float max_speed;
	float max_force; 

	// Sets default values for this pawn's properties
	AMyPawnPath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MovePawn(float DeltaTime);
	void ChangeMode();
	void Seek(FVector position, FVector target, float DeltaTime);
	//FVector truncate(FVector vec, float max);

};
