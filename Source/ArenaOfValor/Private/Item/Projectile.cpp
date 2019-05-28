// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Heros.h"
// Sets default values
AProjectile::AProjectile()
{
    
	// PrimaryActorTick.bCanEverTick = true;
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(5.0f);
    CollisionComp->SetCollisionProfileName("Projectile");
    CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
    
    // Players can't walk on it
    CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
    CollisionComp->CanCharacterStepUpOn = ECB_No;
    
    // Set as root component
    RootComponent = CollisionComp;
    
    // Use a ProjectileMovementComponent to govern this projectile's movement
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = true;
    
    // Die after 3 seconds by default
    InitialLifeSpan = 3.0f;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Only add impulse and destroy projectile if we hit a physics
   // if ((OtherActor != NULL) && (OtherActor != this) )//&& (OtherComp != NULL) )//&& OtherComp->IsSimulatingPhysics())
   // {
        //OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
         AHeros* MyCharacter = Cast<AHeros>(OtherActor);
        MyCharacter->CurHealth-=20;
        if (GEngine) {
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("gogo!")));
        }
        Destroy();
   // }
}


