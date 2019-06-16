// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArenaOfValorCharacter.h"
#include "Turret.generated.h"

UCLASS()
class ARENAOFVALOR_API ATurret : public AArenaOfValorCharacter
{
    GENERATED_BODY()
    
public:
    // Sets default values for this actor's properties
    ATurret();
    virtual void BeginPlay() override;
    virtual float TakeDamage
        (
                float DamageAmount,
                struct FDamageEvent const & DamageEvent,
                class AController * EventInstigator,
                AActor * DamageCauser
        ) override;

protected:

    UPROPERTY(EditDefaultsOnly)
    UStaticMeshComponent* TowerMesh;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
};

