// Fill out your copyright notice in the Description page of Project Settings.

#include "ReactionComponent.h"


// Sets default values for this component's properties
UReactionComponent::UReactionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	this->OnTakeDamage.AddDynamic(this, &UReactionComponent::TakingDamage);
	// ...
}


void UReactionComponent::TakingDamage(AActor* DamageCauser, FDamageProperties AttackUsed)
{
	//Debug Shitz (Attack Damage is just an example)
	UE_LOG(LogTemp, Error, TEXT("%f\n"), AttackUsed.Damage);
}

// Called when the game starts
void UReactionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}
