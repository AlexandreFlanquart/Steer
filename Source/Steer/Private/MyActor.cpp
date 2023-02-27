// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Circuit.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	mass = 15;
	max_speed = 200;
	max_force = 40;
	velocity = FVector(1,1,0);
	sens = 1;

	point = 0;
	int nbPts = 5;
	//FVector Way2[5];

	for (int i = 0; i < nbPts; i++)
	{
		FVector temp = { this->GetActorLocation().X+(i*200), this->GetActorLocation().Y, this->GetActorLocation().Z};
		way1[i] = temp;
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		//GetWorld()->SpawnActor<ACircuit>(way1[i], Rotation, SpawnInfo);
	}

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

FVector truncate(FVector vec, float max) {
	if (vec.Length() == 0)
		return vec;

	if (vec.Length() > max)
		return (max * vec) / vec.Length();
	return vec;
}

void AMyActor::Seek(FVector position, FVector target, float DeltaTime) {
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("SEEK"));
	FVector direction;
	FVector steering;
	FVector force;

	direction = target - position;
	direction = direction * max_speed;
	steering = direction - velocity;

	force = truncate(steering, max_force);
	acceleration = force / mass;
	velocity = truncate(velocity + acceleration, max_speed);
	position = position + velocity * DeltaTime;

	if ((target - position).Length() < 10) {
		if (point < 4 && point > 0)
			point+=sens;
		if(point == 0 && sens > 0)
			point += sens;
	}

	SetActorLocation(position);
	FVector newV = velocity;
	newV.Normalize();
	if (!newV.IsNearlyZero(0.5))
		SetActorRotation(newV.Rotation());
}
void AMyActor::Flee(FVector position, FVector target, float DeltaTime) {
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("FLEE"));

	FVector direction;
	FVector steering;
	FVector force;

	point = 0;
	direction = target - position;
	direction = direction * max_speed;
	steering = -direction - velocity;

	force = truncate(steering, max_force);
	acceleration = force / mass;
	velocity = truncate(velocity + acceleration, max_speed);
	position = position + velocity * DeltaTime;

	SetActorLocation(position);
	FVector newV = velocity;
	newV.Normalize();
	if (!newV.IsNearlyZero(0.5))
		SetActorRotation(newV.Rotation());
}

void AMyActor::Pursuit(FVector position, FVector target, float DeltaTime) {
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("PURSUIT"));

	FVector direction;
	FVector steering;
	FVector force;
	float t;

	point = 0;
	t = 2;
	direction = target - position;
	direction = direction * max_speed * t;
	steering = direction - velocity;

	force = truncate(steering, max_force);
	acceleration = force / mass;
	velocity = truncate(velocity + acceleration, max_speed);
	position = position + velocity * DeltaTime;

	if (velocity.Length() < 10) {
		if (point < 4)
			point++;
	}

	SetActorLocation(position);
	FVector newV = velocity;
	newV.Normalize();
	if (!newV.IsNearlyZero(0.5))
		SetActorRotation(newV.Rotation());
}

void AMyActor::Evade(FVector position, FVector target, float DeltaTime) {
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("EVADE"));

	FVector direction;
	FVector steering;
	FVector force;
	float t;

	point = 0;
	t = 2;
	direction = target - position;
	direction = direction * max_speed * t;
	steering = -direction - velocity;

	force = truncate(steering, max_force);
	acceleration = force / mass;
	velocity = truncate(velocity + acceleration, max_speed);
	position = position + velocity * DeltaTime;

	SetActorLocation(position);
	FVector newV = velocity;
	newV.Normalize();
	if (!newV.IsNearlyZero(0.5))
		SetActorRotation(newV.Rotation());
}

void AMyActor::Arrival(FVector position, FVector target, float DeltaTime) {
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("ARRIVAL"));
	
	FVector direction;
	FVector steering;
	FVector force;
	FVector desired_velocity;
	double distance;
	double slowing_distance;
	double ramped_speed;
	double clipped_speed;

	point = 0;
	direction = target - position;
	distance = direction.Length();
	slowing_distance = 100;
	ramped_speed = max_speed * (distance / slowing_distance);

	if (ramped_speed < max_speed)
		clipped_speed = ramped_speed;
	else
		clipped_speed = max_speed;
	desired_velocity = (clipped_speed / distance) * direction;
	steering = desired_velocity - velocity;

	if ((velocity + acceleration).Length() > max_speed)
		velocity = truncate(velocity + acceleration, max_speed);
	else velocity = velocity + acceleration;
	


	force = truncate(steering, max_force);
	acceleration = force / mass;
	position = position + velocity * DeltaTime;

	SetActorLocation(position);
	FVector newV = velocity;
	newV.Normalize();
	if (!newV.IsNearlyZero(0.5))
		SetActorRotation(newV.Rotation());
}


void AMyActor::Move(float DeltaTime)
{
	FVector direction;
	
	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	FVector position = this->GetActorLocation();
	FVector target = controller->GetPawn()->GetActorLocation();

	switch (GI->mode) {
	case Mode::SEEK:
		Seek(position, target, DeltaTime);
		break;
	case Mode::FLEE:
		Flee(position, target, DeltaTime);
		break;
	case Mode::PURSUIT:
		Pursuit(position, target, DeltaTime);
		break;
	case Mode::EVADE:
		Evade(position, target, DeltaTime);
		break;
	case Mode::ARRIVAL:
		Arrival(position, target, DeltaTime);
		break;
		
	case Mode::WAY1:
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("WAY1"));
		sens = 1;
		if(point == 4)
			Arrival(position, way1[point], DeltaTime);
		else
			Seek(position, way1[point], DeltaTime);
		break;
	case Mode::WAY2:
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("WAY2"));
		if (point == 1 && sens == -1)
			Arrival(position, way1[point], DeltaTime);
		else
			Seek(position, way1[point], DeltaTime);
		if (point == 4)
			sens = -1;

		break;
	case Mode::CIRCUIT:
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("CIRCUIT"));
		Seek(position, way1[point], DeltaTime);
		if (point == 4)
			sens = -1;
		if (point == 0)
			sens = 1;
		break;
	default:
		break;
	}		
}


