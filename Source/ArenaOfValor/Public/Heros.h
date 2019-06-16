// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ArenaOfValorCharacter.h"
#include "Heros.generated.h"

#define HERO_MAX_LEVEL 15


UCLASS(Blueprintable)
class ARENAOFVALOR_API AHeros : public AArenaOfValorCharacter
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FollowCamera;

protected:
    virtual void BeginPlay() override;

public:
    // Sets default values for this character's properties
    AHeros();
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
   
    //  «∑Ò¬˙—™
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    bool HealthIsFull;
    //  «∑Ò¬˙¿∂
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    bool MagicIsFull;
    // Ω±“ ˝
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    int Money;
    // ∆’π•◊ÓµÕπ•ª˜
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    int MiniAttack;
    // ∆’π•◊Ó¥Ûπ•ª˜£®±©ª˜£©£¨ µº π•ª˜‘⁄∂˛’ﬂº‰ÀÊª˙…˙≥…
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    int MaxAttack;
    // ◊Ó¥Û∑®¡¶÷µ
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
    float MaxMagic;
    // µ±«∞∑®¡¶÷µ
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Custom")
    float CurMagic;
    // µ±«∞µ»º∂
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Custom")
    int CurLevel;
    // µ»º∂œ¬µƒµ±«∞æ≠—È÷µ(≤ª∞¸¿®÷Æ«∞µ»º∂£¨…˝º∂º¥«Â¡„)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Custom")
    int CurExp;
    // ∏√µ»º∂œ¬µƒ…˝º∂À˘–Ëæ≠—È
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Custom")
    int LevelUpCostExp;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Custom")
    bool canMove;
    
    // ¥Ú”°∑® ı–≈œ¢£®¥´∏¯¿∂Ãı£©
    UFUNCTION(BlueprintCallable)
    FText setMagicMessage();
    // …˙√¸÷µ «∑Ò∫œ∑®
    UFUNCTION(BlueprintCallable)
    bool HealthValid();
    // ∑® ı÷µ «∑Òπª Õ∑≈ººƒ‹
    UFUNCTION(BlueprintCallable)
    bool MagicValid(float skillCost);
    
    UFUNCTION(BlueprintCallable)
    bool BuySomething(int cost);
    
    // 更新血量
    UFUNCTION(BlueprintCallable)
    void UpdateHealth(float delta);
    // 更新魔法值
    UFUNCTION(BlueprintCallable)
    void UpdateMagic(float delta);
    
    UFUNCTION(BlueprintCallable)
    void AddHealth(float delta);
    
    UFUNCTION(BlueprintCallable)
    void AddMagic(float delta);

    UFUNCTION(BlueprintCallable)
    void setDeath();

    UFUNCTION(BlueprintCallable)
    void reBorn();

    UFUNCTION(BlueprintCallable)
    void LevelUp();
    // 随着时间增加慢慢回血回蓝增加金币经验
    UFUNCTION(BlueprintCallable)
    void Refill();
    
    UFUNCTION(BlueprintCallable, Category = "Custom")
    void BackHome();

    UFUNCTION(BlueprintCallable, Category = "Custom")
    void checkAndAttack(float radius, float damage);

    TArray<AActor*> TargetActors;


};

