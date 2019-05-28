// Fill out your copyright notice in the Description page of Project Settings.


#include "Yase.h"

// Sets default values
AYase::AYase()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
  
}

// Called when the game starts or when spawned
void AYase::BeginPlay()
{
    Super::BeginPlay();
    this->MaxHealth=500;
}

// Called every frame
void AYase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

// Called to bind functionality to input
void AYase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}


