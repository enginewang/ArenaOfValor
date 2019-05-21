// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "MinionPawn.generated.h"

UCLASS()
class ARENAOFVALOR_API AMinionPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMinionPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector DestinationLocation;
	FVector CurrentLocation;
	FVector PointLocation;
	float InterpSpeed;

	UFUNCTION(BlueprintCallable, Category = "Stupid Minion")
		void MoveBetweenTwoPoints(ATargetPoint* Point, float Speed);
};
