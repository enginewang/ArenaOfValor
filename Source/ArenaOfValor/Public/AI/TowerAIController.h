#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/TextRenderComponent.h"
#include "DrawDebugHelpers.h"
#include "TowerAIController.generated.h"

UCLASS()
class ARENAOFVALOR_API ATowerAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	const int STATE__IDLE = 1;
	const int STATE__ATTACK = 2;

	int CurrentState;
	void ExecuteIdleState();
	void ExecuteAttackState();
	bool HasHit(FHitResult &Hit);

};

