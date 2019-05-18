// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerAIController.h"
#include "Engine/Engine.h"
#include "ArenaOfValor.h"

void ATowerAIController::BeginPlay() {
	Super::BeginPlay();

	CurrentState = STATE__IDLE;
}

void ATowerAIController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if (CurrentState == STATE__IDLE) {
		ExecuteIdleState();
	}
	else if (CurrentState == STATE__ATTACK) {
		ExecuteAttackState();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Invalid State: %d"), CurrentState);
		CurrentState = STATE__IDLE;
	}
}

void ATowerAIController::ExecuteIdleState() {
	FHitResult Hit;
	if (HasHit(Hit)) {
		CurrentState = STATE__ATTACK;
	}
	else {
		TArray<UTextRenderComponent*> Comps;
		GetPawn()->GetComponents(Comps);
		if (Comps.Num() != 1) { UE_LOG(LogTemp, Error, TEXT("Missing Text widget!")); return; }
		Comps[0]->SetText(FText::FromString("I'm Idling"));
		Comps[0]->SetTextRenderColor(FColor::Green);
		CurrentState = STATE__IDLE;
	}

}

void ATowerAIController::ExecuteAttackState() {
	FHitResult Hit;
	if (HasHit(Hit)) {
		TArray<UTextRenderComponent*> Comps;
		GetPawn()->GetComponents(Comps);
		if (Comps.Num() != 1) { UE_LOG(LogTemp, Error, TEXT("Missing Text widget!")); return; }
		Comps[0]->SetText(FText::FromString("I'm Attacking"));
		Comps[0]->SetTextRenderColor(FColor::Red);
	}
	else {
		CurrentState = STATE__IDLE;
	}
}

bool ATowerAIController::HasHit(FHitResult &HitOut) {
	static FName SweepTest = TEXT("SweepTest");

	FCollisionQueryParams TraceParams(SweepTest, false, GetPawn());
	FVector Start = GetPawn()->GetActorLocation();
	FVector End = Start;
	float Radius = 500.0f;

	//GetWorld()->DebugDrawTraceTag = SweepTest;	
	FVector YAxis = FVector(0.f, 1.f, 0.f);
	FVector ZAxis = FVector(1.f, 0.f, 0.f);
	DrawDebugCircle(GetWorld(), Start, Radius, 50, FColor::Red, false, -1, 0, 10, YAxis, ZAxis, false);

	bool Found = GetWorld()->SweepSingleByObjectType(
		HitOut,
		Start,
		End,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
		FCollisionShape::MakeSphere(Radius),
		TraceParams);
	return Found;
}
