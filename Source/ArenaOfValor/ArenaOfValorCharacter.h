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
#define NEUTRAL_SIDE 2
#define SMAP_RED_HOME_X 5000


class UInputComponent;
class USphereComponent;
class UWidgetComponent;

UCLASS(config=Game)
class AArenaOfValorCharacter : public ACharacter
{
    GENERATED_BODY()
    
    UPROPERTY(VisibleDefaultsOnly, Category = "Custom")
    class USkeletalMeshComponent* CharacterMesh;
    
public:
    AArenaOfValorCharacter();
    
    virtual void BeginPlay() override;
    
protected:
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom")
    USphereComponent* AttackRangeComp;
    
    void OnResetVR();
    
    void MoveForward(float Value);
    
    void MoveRight(float Value);
    
    void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
    
    void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
    
    UFUNCTION()
    void OnAttackCompBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
    void OnRetriggerAttackStrike();
    
    UFUNCTION(BlueprintCallable, Category = "Custom")
    void PerformAttackDamage(AActor* HitActor);
    
protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
public:
    virtual void Tick(float DeltaTime) override;
    
    // ∫Ï∑ΩŒ™0£¨¿∂∑ΩŒ™1
  
    
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    int MySide;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    bool isAlive;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    float AttackRadius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    FVector CurPosition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    float MaxHealth;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Custom")
    float CurHealth;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Custom")
    float AttackDamage;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Custom")
    float AttackCooldown;
    
    UFUNCTION(BlueprintCallable)
    FText setHealthMessage();
    
    UFUNCTION(BlueprintCallable)
    float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);
    
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    TArray<AActor*> ActorsInRadius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    TSubclassOf<AActor> ActorFilter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    TArray<AArenaOfValorCharacter*> TargetedActors;
    
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    
private:
    FTimerHandle AttackTimeHandler;
    
    float LastAttackTime;
};


