//
//  BaseAIController.hpp
//  ArenaOfValor

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ArenaOfValorCharacter.h"
#include "ARAIController.generated.h"

UCLASS()
class ACTIONRPGGAME_API ABaseAIController : public AAIController
{
    GENERATED_BODY()
public:
    virtual void Possess(class APawn* InPawn) override;
    virtual void Tick(float DeltaSeconds) override;
    
    AArenaOfValorCharacters* TargetActors;
    
    bool dest1;
    bool dest2;
    bool atHome;
    bool onTheWay;
    
    float waitTime;
    
    FTimerHandle waitTimerHandle;
};
