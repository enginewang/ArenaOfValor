// 所有actor的基类

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "Components/ProgressBar.h"
#include <vector>
#include "ArenaOfValorCharacter.generated.h"

// 声明一些default变量
#define DEFAULT_RADIUS 100
#define RED_SIDE 0
#define BLUE_SIDE 1
#define NEUTRAL_SIDE 2
#define SMAP_RED_HOME_X 5000

// 组件，包括输入组件、视图组件、Sphere组件等
class UInputComponent;
class USphereComponent;
class UWidgetComponent;

// 继承自引擎中的Character
UCLASS(config=Game)
class AArenaOfValorCharacter : public ACharacter
{
    GENERATED_BODY()
    // 骨架Mesh，就是皮肤
    UPROPERTY(VisibleDefaultsOnly, Category = "Custom")
    class USkeletalMeshComponent* CharacterMesh;
    
public:
    AArenaOfValorCharacter();
    // 开始时触发该函数
    virtual void BeginPlay() override;
    
protected:
    // 攻击范围
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom")
    USphereComponent* AttackRangeComp;

    // VR输入，不过这里也用不到
    void OnResetVR();
    // 移动
    void MoveForward(float Value);
    void MoveRight(float Value);
    // 触控
    void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
    void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
    // 攻击范围产生重合触发
    UFUNCTION()
    void OnAttackCompBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    // 攻击
    void OnRetriggerAttackStrike();
    UFUNCTION(BlueprintCallable, Category = "Custom")
    void PerformAttackDamage(AActor* HitActor);
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
public:
    // 每帧调用
    virtual void Tick(float DeltaTime) override;

    // 所处哪一边（红、蓝、中立）
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    int MySide;

    // 是否存活
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    bool isAlive;

    // 攻击范围
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    float AttackRadius;

    //  当前位置
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    FVector CurPosition;

    // 最高血量
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    float MaxHealth;

    // 目前血量（非常重要）
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")//, ReplicatedUsing = OnRep_CurHealthChange)
    float CurHealth;

    // 攻击力
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Custom")
    float AttackDamage;

    // 攻击冷却（不过后面换了逻辑）
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Custom")
    float AttackCooldown;

    // 输出生命信息
    UFUNCTION(BlueprintCallable)
    FText setHealthMessage();

    // 受到伤害
    UFUNCTION(BlueprintCallable)
    float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);

    // 攻击范围内的actors数组
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    vector<AActor*> ActorsInRadius;

    // actor筛选（不过后面换了逻辑）
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    TSubclassOf<AActor> ActorFilter;

    //UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    //vector<AArenaOfValorCharacter*> TargetedActors;
    
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    
    UFUNCTION()
    void OnRep_CurHealthChange();
    
private:
    FTimerHandle AttackTimeHandler;
    float LastAttackTime;
};


