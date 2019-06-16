// Fill out your copyright notice in the Description page of Project Settings.


#include "Minions.h"

// Sets default values
AMinions::AMinions()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMinions::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMinions::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

