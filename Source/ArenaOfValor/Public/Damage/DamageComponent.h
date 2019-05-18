// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.generated.h"



UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Physical,
	Magical,
	Enviroment
};


UENUM(BlueprintType)
enum class EDamageEffect : uint8
{
	Direct,
	Stun,
	Dot,
	Madness
};


UENUM(BlueprintType)
enum class EAreaOrigin : uint8
{
	Self,
	Target,
	Ground
};

UENUM(BlueprintType)
enum class EAreaType : uint8
{
	Circle,
	Cone
};



USTRUCT(BlueprintType)
struct FDamageProperties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Property")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Property")
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Property")
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Property")
	EDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Property")
	EDamageEffect DamageEffect;

	//If IsArea and IsPierce are not set to true their own properties are not Editable
	//If both are not set the damage is to apply to the single target
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Property", meta = (EditCondition = "!IsPierce"))
	bool IsArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Property", meta = (EditCondition = "IsArea"))
	float AreaRay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Property", meta = (EditCondition = "IsArea"))
	EAreaType AreaType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Property", meta = (EditCondition = "IsArea"))
	EAreaOrigin AreaOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Property", meta = (EditCondition = "!IsArea"))
	bool IsPierce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Property", meta = (EditCondition = "IsPierce"))
	float PierceLenght;

	//probably will be changed with an angle calculated starting from the Damage Causer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Property", meta = (EditCondition = "IsPierce"))
	FVector PierceDirection;


};



UCLASS( ClassGroup=(Damage), meta=(BlueprintSpawnableComponent) )
class ARENAOFVALOR_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

	//Delegate used to apply the damage
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FApplyDamageDelegate, AActor*, DamagedActor, FDamageProperties, AttackUsed);

public:
	// Sets default values for this component's properties
	UDamageComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TArray<FDamageProperties> AttacksAvailable;

	//Delegate that has to be called when a damaged is caused
	UPROPERTY(BlueprintCallable)
	FApplyDamageDelegate OnApplyDamage;

	//Function Called when OnApplyDamage is triggered (Broadcast)
	UFUNCTION()
	void DamageApplication(AActor* DamagedActor, FDamageProperties AttackUsed);

	//Just a debug function to call in the owner BP to check if everything is working
	UFUNCTION(BlueprintCallable)
	void CauseDamage();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


};