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
    
public:
    // Sets default values for this character's properties
    AHeros();
    
    UFUNCTION(BlueprintCallable, Category = "Custom")
    void BackHome();
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    
    //  «∑ÒªÓ◊≈
   
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
    // ¥Ú”°∑® ı–≈œ¢£®¥´∏¯¿∂Ãı£©
    UFUNCTION(BlueprintCallable)
    FText setMagicMessage();
    // …˙√¸÷µ «∑Ò∫œ∑®
    UFUNCTION(BlueprintCallable)
    bool HealthValid();
    // ∑® ı÷µ «∑Òπª Õ∑≈ººƒ‹
    UFUNCTION(BlueprintCallable)
    bool MagicValid(float skillCost);
    // ∏¸–¬…˙√¸÷µ£¨’˝ ˝¥˙±Ì‘ˆº”—™¡ø£¨∏∫ ˝Œ™ø€—™¡ø£®µ¿æﬂ÷– π”√£©
    UFUNCTION(BlueprintCallable)
    void UpdateHealth(float delta);
    // ∏¸–¬∑® ı÷µ£¨’˝ ˝¥˙±Ì‘ˆº”¿∂Ãı£¨∏∫ ˝Œ™ø€¿∂Ãı£®µ¿æﬂ÷– π”√£©
    UFUNCTION(BlueprintCallable)
    void UpdateMagic(float delta);
    // …Ë÷√À¿Õˆ
    UFUNCTION(BlueprintCallable)
    void setDeath();
    // ÷ÿ…˙
    UFUNCTION(BlueprintCallable)
    void reBorn();
    // …˝º∂
    UFUNCTION(BlueprintCallable)
    void LevelUp();
    // ’˝≥£ ±º‰µƒ…˙√¸÷µ°¢∑® ı÷µª∫¬˝ª÷∏¥
    UFUNCTION(BlueprintCallable)
    void Refill();
};

