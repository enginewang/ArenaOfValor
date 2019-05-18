// Fill out your copyright notice in the Description page of Project Settings.

#include "MinionPawn.h"


// Sets default values
AMinionPawn::AMinionPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMinionPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMinionPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DestinationLocation = FMath::VInterpTo(CurrentLocation, PointLocation, DeltaTime, InterpSpeed);
	SetActorLocation(DestinationLocation);
	CurrentLocation = DestinationLocation;
}

// Called to bind functionality to input
void AMinionPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMinionPawn::MoveBetweenTwoPoints(ATargetPoint* Point, float Speed)
{
	CurrentLocation = GetActorLocation();
	PointLocation = Point->GetActorLocation();
	InterpSpeed = Speed;
}
