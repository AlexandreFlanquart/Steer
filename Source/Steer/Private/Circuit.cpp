// Fill out your copyright notice in the Description page of Project Settings.

#include "Circuit.h"



// Sets default values
ACircuit::ACircuit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACircuit::BeginPlay()
{
	Super::BeginPlay();
	/*
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	mesh->SetupAttachment(RootComponent);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));

	if (BaseMeshAsset.Object)
	{
		mesh->SetStaticMesh(BaseMeshAsset.Object);
	}*/
	
}

// Called every frame
void ACircuit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

