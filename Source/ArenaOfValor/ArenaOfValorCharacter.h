// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "Components/ProgressBar.h"
#include "ArenaOfValorCharacter.generated.h"


#define DEFAULT_RADIUS 100
#define RED_SIDE 0
#define BLUE_SIDE 1
#define UNDEFINED_SIDE 2
#define SMAP_RED_HOME_X 5000


class UInputComponent;
class USphereComponent;

UCLASS(config=Game)
class AArenaOfValorCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* CharacterMesh;
	
public:
	AArenaOfValorCharacter();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom")
		USphereComponent* SphereComp;

	void OnResetVR();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);


protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void Tick(float DeltaTime) override;

	// 红方为0，蓝方为1
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
		int MySide;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
		float AttackRadius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
		FVector CurPosition;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
		float MaxHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Custom")
		float CurHealth;

	UFUNCTION(BlueprintCallable)
		FText setHealthMessage();

	//UFUNCTION(BlueprintCallable)
		//virtual void FindEnemies();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
		UProgressBar* FloatHealthBar;


	// 攻击范围内的Actor列表
	//TArray<AActor*> ActorsInRadius;

	// 可以遭受攻击伤害的敌人列表
	//TSet<AArenaOfValorCharacter*> TargetedActors;
};

