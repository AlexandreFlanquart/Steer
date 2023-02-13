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
	target = controller->GetPawn()->GetActorLocation();
	mass = 15;
	max_speed = 200;
	max_force = 40;
	velocity = FVector(1,1,0);
	position = this->GetActorLocation();

	point = 0;
	int nbPts = 5;
	//FVector Way2[5];

	for (int i = 0; i < nbPts; i++)
	{
		FVector temp = { this->GetActorLocation().X+(i*20), this->GetActorLocation().Y, this->GetActorLocation().Z};
		way1[i] = temp;
		//Way2[i] = temp;
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		GetWorld()->SpawnActor<ACircuit>(way1[i], Rotation, SpawnInfo);
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


void AMyActor::Move(float DeltaTime)
{
	FVector direction;
	FVector steering;
	FVector force;
	FVector desired_velocity;
	double distance;
	double slowing_distance;
	double ramped_speed;
	double clipped_speed;
	float t;
	
	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	position = this->GetActorLocation();
	target = controller->GetPawn()->GetActorLocation();

	switch (GI->mode) {
	case Mode::SEEK:
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("SEEK"));
		direction = target - position;
		direction = direction * max_speed;
		steering = direction - velocity;

		force = truncate(steering, max_force);
		acceleration = force / mass;
		velocity = truncate(velocity + acceleration, max_speed);
		position = position + velocity * DeltaTime;
		
		break;
	case Mode::FLEE:
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("FLEE"));
		direction = target - position;
		direction = direction * max_speed;
		steering = -direction - velocity;

		force = truncate(steering, max_force);
		acceleration = force / mass;
		velocity = truncate(velocity + acceleration, max_speed);
		position = position + velocity * DeltaTime;

		break;
	case Mode::PURSUIT:
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("PURSUIT"));
		t = 2;
		direction = target - position;
		direction = direction * max_speed * t;
		steering = direction - velocity;

		force = truncate(steering, max_force);
		acceleration = force / mass;
		velocity = truncate(velocity + acceleration, max_speed);
		position = position + velocity * DeltaTime;

		break;
	case Mode::EVADE:
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("EVADE"));
		t = 2;
		direction = target - position;
		direction = direction * max_speed * t;
		steering = -direction - velocity;

		force = truncate(steering, max_force);
		acceleration = force / mass;
		velocity = truncate(velocity + acceleration, max_speed);
		position = position + velocity * DeltaTime;

		break;
	case Mode::ARRIVAL:
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("ARRIVAL"));
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
		break;
		
	case Mode::WAY1:
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("WAY1"));
		position = way1[point];
		GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("pos %s"), *position.ToString()));
		direction = target - position;
		direction = direction * max_speed;
		steering = direction - velocity;

		force = truncate(steering, max_force);
		acceleration = force / mass;
		velocity = truncate(velocity + acceleration, max_speed);
		position = position + velocity * DeltaTime;
		if (velocity.Length() < 0.5) {
			if (point < 4)
				point++;
			else
				point = 0;
		}
	case Mode::WAY2:
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("WAY2"));
		position = way1[point];
		direction = target - position;
		direction = direction * max_speed;
		steering = direction - velocity;

		force = truncate(steering, max_force);
		acceleration = force / mass;
		velocity = truncate(velocity + acceleration, max_speed);
		position = position + velocity * DeltaTime;
		if (velocity.Length() < 0.5) {
			if (point < 4)
				point++;
			else
				point = 0;
		}
	case Mode::CIRCUIT:
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("CIRCUIT"));
		position = way1[point];
		direction = target - position;
		direction = direction * max_speed;
		steering = direction - velocity;

		force = truncate(steering, max_force);
		acceleration = force / mass;
		velocity = truncate(velocity + acceleration, max_speed);
		position = position + velocity * DeltaTime;
		if (velocity.Length() < 0.5) {
			if (point < 4)
				point++;
			else
				point = 0;
		}

	default:
		break;
	}

	SetActorLocation(position);
	FVector newV = velocity;
	newV.Normalize();
	if(!newV.IsNearlyZero(0.5))
		SetActorRotation(newV.Rotation());
		
}


