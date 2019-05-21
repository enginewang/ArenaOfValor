// Fill out your copyright notice in the Description page of Project Settings.

#include "Damage/DamageComponent.h" 
#include "Damage/ReactionComponent.h"
#include "Heros.h"

// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	this->OnApplyDamage.AddDynamic(this, &UDamageComponent::DamageApplication);
	// ...
}



void UDamageComponent::DamageApplication(AActor* DamagedActor, FDamageProperties AttackUsed)
{
	//Debug Shitz (Attack Damage is just an example)
	//Test to check if this is gonna trigger the ReactionComponent too
	UE_LOG(LogTemp, Warning, TEXT("%f\n"), AttackUsed.Damage);
	class AHeros* DamagedRef = Cast<AHeros>(DamagedActor);
	if(DamagedRef)
	{
		DamagedRef->ReactionComp->OnTakeDamage.Broadcast(this->GetOwner(), AttackUsed);
	}
}



void UDamageComponent::CauseDamage()
{
	//You need to add new Available Attacks in the Owner BP, it is just gonna randomize one of them
	if(AttacksAvailable.Num()>0) 
		this->OnApplyDamage.Broadcast(this->GetOwner(), AttacksAvailable[FMath::RandRange(1, AttacksAvailable.Num()) - 1]);
	else
	UE_LOG(LogTemp, Error, TEXT("YOU NEED TO CREATE MORE AVAILABLE ATTACKS ON THE OWNER\n"));
}
