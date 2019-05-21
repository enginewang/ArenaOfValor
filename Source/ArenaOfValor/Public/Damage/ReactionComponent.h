// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.h"
#include "ReactionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENAOFVALOR_API UReactionComponent : public UActorComponent
{
	GENERATED_BODY()

	//Delegate Used On Damage Taken 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTakeDamageDelegate, AActor*, DamageCauser, FDamageProperties, AttackUsed);

public:	
	// Sets default values for this component's properties
	UReactionComponent();

	//Delegate Called in DamageComponent when a damage is applied
	UPROPERTY(BlueprintCallable)
	FTakeDamageDelegate OnTakeDamage;

	//Function called when OnTakeDamage is triggered (broadcast)
	UFUNCTION()
	void TakingDamage(AActor* DamageCauser, FDamageProperties AttackUsed);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
