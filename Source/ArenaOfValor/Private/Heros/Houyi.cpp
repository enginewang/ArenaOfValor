#include "Houyi.h"
#include <map>

const map<string, int> HouyiAbilityCost = {
        { "Q", 15 },
        { "E", 25 },
        { "R", 30 },
        { "U", 40 }
};

// Sets default values
AHouyi::AHouyi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SpawnFireBallPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
    SpawnFireBallPoint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHouyi::BeginPlay()
{
    Super::BeginPlay();
    this->MaxHealth=100;
    SpawnFireBallPoint->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Muzzle"));
}

// Called every frame
void AHouyi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHouyi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAction("AbilityQ", IE_Pressed, this, &AYase::AbilityQ);
    PlayerInputComponent->BindAction("AbilityQ", IE_Pressed, this, &AYase::AbilityE);
    PlayerInputComponent->BindAction("AbilityQ", IE_Pressed, this, &AYase::AbilityR);
    PlayerInputComponent->BindAction("AbilityQ", IE_Pressed, this, &AYase::AbilityU);
}

void AHouyi::AbilityQ()
{
    FTransform SpawnTransform = SpawnProjectilePoint->GetComponentTransform();
    auto SpawnPrt = GetWorld()->SpawnActor(Projectile, &SpawnTransform);
    SpawnedProjectile = (AProjectile*)GetWorld()->SpawnActor(Projectile, SpawnTransform);
    FTimerHandle Timer;
    GetWorldTimerManager().SetTimer(Timer, this, &AHouyi::AbilityQ, 1.0f, false);
}

