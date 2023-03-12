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
	graph = Graph(GetWorld());
	GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	m = true;

	mass = 15;
	max_speed = 200;
	max_force = 70;
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
	InputComponent->BindAction("SwitchMode", IE_Pressed, this, &AMyPawnPath::ChangeMode);

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

	if (m) {
		GI->modePath = static_cast<ModePath>(0);
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("PATH"));
	}	
	else {
		GI->modePath = static_cast<ModePath>(1);
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("LOOP"));
	}
		
}

void AMyPawnPath::MovePawn(float DeltaTime) {
	FVector position = this->GetActorLocation();
	float dist = 0;

	if (!path.empty()) { // if path in progress
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, path[0]->GetName());
		path[0]->isNext = true;
		Seek(position, path[0]->GetActorLocation(), DeltaTime);
		//dist = this->GetActorLocation().Length() - path[0]->GetActorLocation().Length();
		//dist = position.Distance(position, path[0]->GetActorLocation());
		dist = FVector::Dist(position, path[0]->GetActorLocation());
		if (abs(dist) <= 50) { // if arrive
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("ARRIVE"));
			path.erase(path.begin());
		}
	}
	else { // else search next path
		if (!listNodes.IsEmpty()) {
			GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Red, listNodes[0]->GetName());
			path = graph.AStar(start, listNodes[0]);
			if (GI->modePath == ModePath::LOOP) {// check if need to loop
				//listNodes.Add(listNodes[0]);
			}
			listNodes.RemoveAt(0);
		}

	}
}
