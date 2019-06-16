// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Heros.h"
#include "Projectile.cpp"
#include "Houyi.generated.h"

UCLASS()
class ARENAOFVALOR_API AHouyi : public AHeros
{
	GENERATED_BODY()

private:
    // 单例模式，放在private下
	AHouyi();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    static AHouyi& GetInstance(){
        static AHouyi instance;
        return instance;
    }
    AHouyi(const AHouyi&) = delete;
    AHouyi& operator=(const AHouyi&) = delete;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY()
    USceneComponent* SpawnFireBallPoint;

    UFUNCTION()
    void AbilityQ();

    UFUNCTION()
    void AbilityE();

    UFUNCTION()
    void AbilityR();

    UFUNCTION()
    void AbilityU();
};
