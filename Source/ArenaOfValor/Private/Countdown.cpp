// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Countdown.h"
#include "Components/TextRenderComponent.h"
#include "ArenaOfValor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACountdown::ACountdown()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    
    CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CounterdownNumber"));
    CountdownText->SetHorizontalAlignment(EHTA_Center);
    CountdownText->SetWorldSize(150.0f);
    RootComponent = CountdownText;
    
    CountdownTime = 3;
    OriginCountdownTime = CountdownTime;
}

// Called when the game starts or when spawned
void ACountdown::BeginPlay()
{
    Super::BeginPlay();
    UpdateTimerDisplay();
    GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::AdvanceTimer, 1.2f, true);
}

void ACountdown::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

// ∞—CountdownTimeœ‘ æµΩ”Œœ∑÷–
void ACountdown::UpdateTimerDisplay()
{
    CountdownText->SetText(FText::FromString(FString::FromInt(FMath::Max(CountdownTime, 0))));
}

void ACountdown::AdvanceTimer() {
    --CountdownTime;
    UpdateTimerDisplay();
    if (CountdownTime==0) {
        CountdownFinished();
    }
    if (CountdownTime < 0) {
        GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
        CountdownText->SetText(FText::FromString(" "));
    }
}

void ACountdown::CountdownFinished_Implementation() {
    CountdownText->SetText(FText::FromString("Go!"));
}



void ACountdown::StopCountdown_Implementation() {
    CountdownText->SetText(FText::FromString(FString::FromInt(OriginCountdownTime)));
}

float ACountdown::ReturnTotalSecond() {
    float realTimeSecond = UGameplayStatics::GetRealTimeSeconds(GetWorld());
    return realTimeSecond;
}

