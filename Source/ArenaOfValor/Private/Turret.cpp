#include "Turret.h"
#include "ArenaOfValorCharacter.h"


// Sets default values
ATurret::ATurret()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh"));
    TowerMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    attackRadius = CreateDefaultSubobject<USphereComponent>(TEXT("attackRadius"));
    attackRadius->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    attackRadius->bGenerateOverlapEvents = true;
    attackRadius->OnComponentBeginOverlap.AddDynamic(this, &ATowerBase::TriggerEnter);
    attackRadius->OnComponentEndOverlap.AddDynamic(this, &ATowerBase::TriggerExit);
    bCanBeDamaged = true;
    this->MaxHealth = 500;
    this->CurHealth = this->MaxHealth
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}


