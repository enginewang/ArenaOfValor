// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Countdown.generated.h"


UCLASS()
class ARENAOFVALOR_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACountdown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaSeconds) override;
	// 运行时长，以秒计
	UPROPERTY(EditAnywhere)
	int32 CountdownTime;
	UTextRenderComponent* CountdownText;
	int32 OriginCountdownTime;
	void UpdateTimerDisplay();
	void AdvanceTimer();
	UFUNCTION(BlueprintNativeEvent)
	void CountdownFinished();
	virtual void CountdownFinished_Implementation();
	FTimerHandle CountdownTimerHandle;
	UFUNCTION(BlueprintNativeEvent)
	void StopCountdown();
	virtual void StopCountdown_Implementation();
	void DeleteCountdown();
	float ReturnTotalSecond();
};
