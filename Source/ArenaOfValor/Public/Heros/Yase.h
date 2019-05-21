// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Heros.h"
#include "Yase.generated.h"

UCLASS(Blueprintable)
class ARENAOFVALOR_API AYase : public AHeros
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AYase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
