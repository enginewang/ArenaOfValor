#include "Daji.h"
#include <map>

const map<string, int> DajiAbilityCost = {
        { "Q", 10 },
        { "E", 30 },
        { "R", 40 },
        { "U", 60 }
};

// Sets default values
ADaji::ADaji()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADaji::BeginPlay()
{
	Super::BeginPlay();
    this->MaxHealth=200;
}

// Called every frame
void ADaji::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADaji::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAction("AbilityQ", IE_Pressed, this, &AYase::AbilityQ);
    PlayerInputComponent->BindAction("AbilityQ", IE_Pressed, this, &AYase::AbilityE);
    PlayerInputComponent->BindAction("AbilityQ", IE_Pressed, this, &AYase::AbilityR);
    PlayerInputComponent->BindAction("AbilityQ", IE_Pressed, this, &AYase::AbilityU);
}

