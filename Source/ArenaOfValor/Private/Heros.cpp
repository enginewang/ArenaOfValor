// Fill out your copyright notice in the Description page of Project Settings.


#include "Heros.h"
#include "Components/CapsuleComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "ArenaOfValorCharacter.h"
#include "Countdown.h"

// Sets default values
AHeros::AHeros()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    
    //DamageComp = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComp"));
    //ReactionComp = CreateDefaultSubobject<UReactionComponent>(TEXT("ReactionComp"));
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character
    CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
    // No
}

// Called when the game starts or when spawned
void AHeros::BeginPlay()
{
    Super::BeginPlay();
    
    isAlive = true;
    canMove = true;
    CurLevel = 1;
    CurExp = 0;
    LevelUpCostExp = 60;
    MaxHealth = 100; // default
    CurHealth = MaxHealth;
    MaxMagic = 100; // default
    CurMagic = MaxMagic;
    FTimerHandle DeltaTimeRefillHandler;
    GetWorldTimerManager().SetTimer(DeltaTimeRefillHandler, this, &AHeros::Refill, 3.0f, true);
}

// Called every frame
void AHeros::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if(isAlive){
        if (CurHealth >= MaxHealth) {
            HealthIsFull = true;
            CurHealth = MaxHealth;
        }else{
            HealthIsFull = false;
        }
        if (CurMagic >= MaxMagic) {
            MagicIsFull = true;
            CurMagic = MaxMagic;
        }else{
            MagicIsFull = false;
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
    if(CurHealth<0)CurHealth=0;
    return true;
}

bool AHeros::MagicValid(float skillCost) {
    if (CurMagic > MaxMagic) {
        CurMagic = MaxMagic;
        MagicIsFull = true;
    }
     if(CurMagic<0)CurMagic=0;
    if (CurMagic < skillCost) {
        return false;
    }
    else {
        return true;
    }
}

bool AHeros::BuySomething(int cost) {
    if (Money < cost) {
        return false;
    }
    else {
        Money-=cost;
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
        ;
    }
}

void AHeros::LevelUp() {
    if (CurLevel < HERO_MAX_LEVEL) {
        CurLevel += 1;
        CurExp = 0;
        MaxHealth += 10;
        MaxMagic += 5;
        AttackDamage += 2;
        LevelUpCostExp += 20;
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
    BackHome();
}


void AHeros::Refill() {
    float deltaHealth = 1;
    float deltaMagic = 1;
    float deltaMoney = 1;
    float deltaExp = 1;
    if(isAlive){
    if(HealthIsFull==false) {
        CurHealth += deltaHealth;
    }
    if(MagicIsFull==false) {
        CurMagic += deltaMagic;
    }
    CurExp += deltaExp;
    Money += deltaMoney;
    }
}

void AHeros::AddHealth(float delta){
    if(CurHealth<MaxHealth){
        if(CurHealth+delta>MaxHealth){
            CurHealth=MaxHealth;
        } else{
            CurHealth += delta;
        }
    }
}

void AHeros::AddMagic(float delta){
    if(CurMagic<MaxMagic){
        if(CurMagic+delta>MaxMagic){
            CurMagic=MaxMagic;
        } else{
            CurMagic += delta;
        }
    }
}

void AHeros::checkAndAttack(float radius, float damage){
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArenaOfValorCharacter::StaticClass(), TargetActors);
    for (AArenaOfValorCharacter* Actor : TargetActors) {
        auto thisActor = Cast<AArenaOfValorCharacter>(Actor);
        if (this->getDistanceTo(thisActor) && thisActor->MySide != MySide && thisActor->isAlive==true) {
                thisActor->CurHealth -= this->AttackDamage;
        }
        if(thisActor->CurHealth <= 0){
            this->CurExp += 20;
            this->Money += 300;
        }
    }
}
