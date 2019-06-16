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
    
private:
    // 单例模式，放在private下
    AYase();
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
public:
    static AYase& GetInstance(){
        static AYase instance;
        return instance;
    }
    AYase(const AYase&) = delete;
    AYase& operator=(const AYase&) = delete;
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

