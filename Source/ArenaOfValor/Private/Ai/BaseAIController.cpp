//
//  BaseAIController.cpp

#include "BaseAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationData.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"


ABaseAIController::ABaseAIController(const FObjectInitializer& ObjectInitializer)
{
     dest1 = true;
     dest2 = false;
}



void ABaseAIController::MoveTowardsActor(AActor* ActorTarget)
{
    MoveToActor(ActorTarget, 500.0f, true, true, true, DefaultNavigationFilterClass, true);
}


void ABaseAIController::Possess(APawn * InPawn)
{
    Super::Possess(InPawn);
}

void ABaseAIController::Tick(float DeltaTime)
{
    if (dest1)
    {
        MoveToLocation(targetPosition, 1.0f);
        onTheWay = true;
        destination1 = false;
    }
    
    if (dest2)
    {
        MoveToLocation(homeLocation, 1.0f);
        atHome = true;
        destination2 = false;
    }
}

