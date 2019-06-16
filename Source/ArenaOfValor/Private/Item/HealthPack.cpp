// 亚瑟Q技能种出来的草，可以作为一个物体出现在地图上，吃了可以回血

#include "HealthPack.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ArenaOfValorCharacter.h"
#include "Heros.h"
// Sets default values
AHealthPack::AHealthPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
    MeshComp= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    RootComponent= MeshComp;
    
    
    SphereComp= CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
    SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
    SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
    PlayEffects();
	
}

void AHealthPack::PlayEffects(){
     UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX,GetActorLocation());
}
// Called every frame

void AHealthPack::NotifyActorBeginOverlap(AActor* OtherActor){
    Super::NotifyActorBeginOverlap(OtherActor);
    PlayEffects();
    
    AHeros* MyCharacter = Cast<AHeros>(OtherActor);
    if(MyCharacter){
        MyCharacter->CurHealth+=30;
        MyCharacter->CurMagic+=30;
        MyCharacter->CurExp+=30;
        Destroy();
    }
}
