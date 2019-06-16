// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Heros.h"
#include "Daji.generated.h"

UCLASS()
class ARENAOFVALOR_API ADaji : public AHeros
{
	GENERATED_BODY()

private:
    // 单例模式，放在private下
	ADaji();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    static ADaji& GetInstance(){
        static ADaji instance;
        return instance;
    }
    ADaji(const ADaji&) = delete;
    ADaji& operator=(const ADaji&) = delete;
    // Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION()
    void AbilityQ();

    UFUNCTION()
    void AbilityE();

    UFUNCTION()
    void AbilityR();

    UFUNCTION()
    void AbilityU();
};
