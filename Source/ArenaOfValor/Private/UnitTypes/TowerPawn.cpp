// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerPawn.h"
#include "Components/SphereComponent.h"

#include "DrawDebugHelpers.h"

// Sets default values
ATowerPawn::ATowerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//DetectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Detect Sphere Comp"));
	//DetectSphere->InitSphereRadius(300.0f);
	//DetectSphere->SetCollisionProfileName(TEXT("Trigger"));
	//DetectSphere->SetupAttachment(RootComponent);
	////////
	//DetectSphere->OnComponentBeginOverlap.AddDynamic(this, &ATowerPawn::OnOverlapBegin);
	//DetectSphere->OnComponentEndOverlap.AddDynamic(this, &ATowerPawn::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ATowerPawn::BeginPlay()
{
	Super::BeginPlay();
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 300.0f, 50, FColor::Purple, true, -1, 0, 2);
}

// Called every frame
void ATowerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATowerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATowerPawn::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enter"));
	}
}

void ATowerPawn::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Exit"));
	}
}
