// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	m = 0;
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("SwitchMode", IE_Pressed, this, &AMyPawn::ChangeMode);

}

void AMyPawn::ChangeMode()
{
	if (m == 7)
		m = 0;
	else
		m++;

	GI->mode = static_cast<Mode>(m);
	//GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("Mode : %s"), GI->mode));

}