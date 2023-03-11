// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnPath.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMyPawnPath::AMyPawnPath()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawnPath::BeginPlay()
{
	Super::BeginPlay();
	
	path = vector<AMyNode*>();

	GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	m = 0;

	mass = 15;
	max_speed = 200;
	max_force = 40;
	velocity = FVector(1, 1, 0);
}

// Called every frame
void AMyPawnPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePawn(DeltaTime);

}

// Called to bind functionality to input
void AMyPawnPath::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//InputComponent->BindAction("SwitchMode", IE_Pressed, this, &AMyPawnPath::ChangeMode);

}

FVector Truncate(FVector vec, float max) {
	if (vec.Length() == 0)
		return vec;

	if (vec.Length() > max)
		return (max * vec) / vec.Length();
	return vec;
}

void AMyPawnPath::Seek(FVector position, FVector target, float DeltaTime) {
	
	FVector direction;
	FVector steering;
	FVector force;

	direction = target - position;
	direction = direction * max_speed;
	steering = direction - velocity;

	force = Truncate(steering, max_force);
	acceleration = force / mass;
	velocity = Truncate(velocity + acceleration, max_speed);
	position = position + velocity * DeltaTime;

	SetActorLocation(position);
	FVector newV = velocity;
	newV.Normalize();
	if (!newV.IsNearlyZero(0.5))
		SetActorRotation(newV.Rotation());
}

void AMyPawnPath::ChangeMode() {
	m = !m;
	GI->modePath = static_cast<ModePath>(m);
	if(m)
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("PATH"));
	else
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("LOOP"));
}

void AMyPawnPath::MovePawn(float DeltaTime) {
	FVector position = this->GetActorLocation();
	float dist = 0;

	if (!path.empty()) { // if path in progress
		Seek(position, path[0]->GetActorLocation(), DeltaTime);
		dist = position.Length() - path[0]->GetActorLocation().Length();
		if (abs(dist) <= 2) { // if arrive
			path.erase(path.begin());
		}
	}
	else { // else search next path

	}
	
	/*
	switch (GI->modePath) {
		case ModePath::PATH
			
			break;
		case ModePath::PATH
				
			break;
	}
	Seek(position, target, DeltaTime);
	*/
}
