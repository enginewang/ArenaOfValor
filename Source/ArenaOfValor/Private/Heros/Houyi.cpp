// Fill out your copyright notice in the Description page of Project Settings.


#include "Houyi.h"

// Sets default values
AHouyi::AHouyi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHouyi::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHouyi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHouyi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

