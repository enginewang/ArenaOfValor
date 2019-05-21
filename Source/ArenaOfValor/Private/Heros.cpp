// Fill out your copyright notice in the Description page of Project Settings.


#include "Heros.h"
#include "Components/CapsuleComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "DamageComponent.h"
#include "ReactionComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "ArenaOfValorCharacter.h"
#include "Countdown.h"

// Sets default values
AHeros::AHeros()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	DamageComp = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComp"));
	ReactionComp = CreateDefaultSubobject<UReactionComponent>(TEXT("ReactionComp"));
}

// Called when the game starts or when spawned
void AHeros::BeginPlay()
{
	Super::BeginPlay();

	isAlive = true;
	CurLevel = 1;
	CurExp = 0;
	MaxHealth = 100; // default
	CurHealth = MaxHealth;
	MaxMagic = 100; // default
	CurMagic = MaxMagic;
	FTimerHandle DeltaTimeRefillHandler;
	GetWorldTimerManager().SetTimer(DeltaTimeRefillHandler, this, &AHeros::Refill, 1.0f, true);
}

// Called every frame
void AHeros::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurHealth <= 0) {
		setDeath();
	}
	else {
		LevelUpCostExp = 500 + CurLevel * 50;
		if (CurExp >= LevelUpCostExp) {
			LevelUp();
		}
		else
		{
			;
		}
	}
}

// Called to bind functionality to input
void AHeros::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

FText AHeros::setMagicMessage()
{
	FText message = FText::FromString(FString::Printf(TEXT("Magic: %d / %d"), (int)CurMagic, (int)MaxMagic));
	return message;
}


void AHeros::BackHome() {
	// 获得家的位置
	FVector ActorLocation = GetActorLocation();
	if (MySide){
		ActorLocation.X = -5000;
	}
	else {
		ActorLocation.X = 5000;
	}
	ActorLocation.Y = 0;
	SetActorLocation(ActorLocation, false);
}

bool AHeros::HealthValid() {
	if (CurHealth > MaxHealth) {
		CurHealth = MaxHealth;
		HealthIsFull = true;
		return true;
	}
	else if (CurHealth <= 0) {
		setDeath();
		return false;
	}
	return true;
}

bool AHeros::MagicValid(float skillCost) {
	if (CurMagic > MaxMagic) {
		CurMagic = MaxHealth;
		MagicIsFull = true;
	}
	if (CurMagic < skillCost) {
		return false;
	}
	else {
		return true;
	}
}

void AHeros::UpdateHealth(float delta)
{
	CurHealth += delta;
	HealthValid();
}

void AHeros::UpdateMagic(float delta)
{
	if (MagicValid(-delta)) {
		CurMagic += delta;
	}
	else {
		//蓝条不够释放该技能
		;
	}
}

void AHeros::LevelUp() {
	if (CurLevel < HERO_MAX_LEVEL) {
		CurLevel += 1;
		CurExp = 0;
		//MaxHealth += 10;
		//MaxMagic += 5;
	}
}

void AHeros::setDeath() {
	float rebornTime = 5.0f;
	FTimerHandle RebornTimerHandler;
	isAlive = false;
	GetWorldTimerManager().SetTimer(RebornTimerHandler, this, &AHeros::reBorn, rebornTime, true);
}

void AHeros::reBorn() {
	isAlive = true;
	CurHealth = MaxHealth;
	CurMagic = MaxMagic;
}


void AHeros::Refill() {
	float deltaHealth = 1;
	float deltaMagic = 1;
	float deltaMoney = 1;
	float deltaExp = 1;

	if (CurHealth >= MaxHealth) {
		CurHealth = MaxHealth;
		HealthIsFull = true;
	}
	else {
		HealthIsFull = false;
		CurHealth += deltaHealth;
	}
	if (CurMagic >= MaxMagic) {
		CurMagic = MaxHealth;
		MagicIsFull = true;
	}
	else {
		MagicIsFull = false;
		CurMagic += deltaMagic;
	}	
	CurExp += deltaExp;
	Money += deltaMoney;
}