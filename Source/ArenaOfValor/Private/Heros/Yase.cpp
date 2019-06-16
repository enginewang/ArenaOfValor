// 技能只在C++中声明，因为涉及到动画等素材，C++不好调用，就放在编辑器用蓝图中实现了
#include "Yase.h"
#include <map>

// 亚瑟技能耗蓝的map
const map<string, int> YaseAbilityCost = {
        { "Q", 10 },
        { "E", 20 },
        { "R", 30 },
        { "U", 50 }
};

// Sets default values
AYase::AYase()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AYase::BeginPlay()
{
    Super::BeginPlay();
    this->MaxHealth=500;
}

// Called every frame
void AYase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

// Called to bind functionality to input
void AYase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAction("AbilityQ", IE_Pressed, this, &AYase::AbilityQ);
    PlayerInputComponent->BindAction("AbilityQ", IE_Pressed, this, &AYase::AbilityE);
    PlayerInputComponent->BindAction("AbilityQ", IE_Pressed, this, &AYase::AbilityR);
    PlayerInputComponent->BindAction("AbilityQ", IE_Pressed, this, &AYase::AbilityU);
}


