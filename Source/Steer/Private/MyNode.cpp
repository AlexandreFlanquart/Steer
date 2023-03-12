// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNode.h"

// Sets default values
AMyNode::AMyNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyNode::BeginPlay()
{
	Super::BeginPlay();
	isNext = false;
	cost = 1000;
	dist = 0;
	heuristique = 0;
}

// Called every frame
void AMyNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


