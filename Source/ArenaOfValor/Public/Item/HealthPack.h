// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPack.generated.h"

class USphereComponent;

UCLASS()
class ARENAOFVALOR_API AHealthPack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* MeshComp;
    
    
    UPROPERTY(VisibleAnywhere, Category =  "Components")
    USphereComponent* SphereComp;
    
    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    UParticleSystem* PickupFX;
    
    void PlayEffects();
    
    
    
    

public:	
	// Called every frame
	
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
