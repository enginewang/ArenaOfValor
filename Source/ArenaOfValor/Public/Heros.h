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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
		class UDamageComponent* DamageComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
		class UReactionComponent* ReactionComp;

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


	// 是否活着
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
		bool isAlive;
	// 是否满血
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
		bool HealthIsFull;
	// 是否满蓝
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
		bool MagicIsFull;
	// 金币数
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
		int Money;
	// 普攻最低攻击
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
		int MiniAttack;
	// 普攻最大攻击（暴击），实际攻击在二者间随机生成
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
		int MaxAttack;
	// 最大法力值
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
		float MaxMagic;
	// 当前法力值
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Custom")
		float CurMagic;
	// 当前等级
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Custom")
		int CurLevel;
	// 等级下的当前经验值(不包括之前等级，升级即清零)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Custom")
		int CurExp;
	// 该等级下的升级所需经验
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Custom")
		int LevelUpCostExp;
	// 打印法术信息（传给蓝条）
	UFUNCTION(BlueprintCallable)
		FText setMagicMessage();
	// 生命值是否合法
	UFUNCTION(BlueprintCallable)
		bool HealthValid();
	// 法术值是否够释放技能
	UFUNCTION(BlueprintCallable)
		bool MagicValid(float skillCost);
	// 更新生命值，正数代表增加血量，负数为扣血量（道具中使用）
	UFUNCTION(BlueprintCallable)
		void UpdateHealth(float delta);
	// 更新法术值，正数代表增加蓝条，负数为扣蓝条（道具中使用）
	UFUNCTION(BlueprintCallable)
		void UpdateMagic(float delta);
	// 设置死亡
	UFUNCTION(BlueprintCallable)
		void setDeath();
	// 重生
	UFUNCTION(BlueprintCallable)
		void reBorn();
	// 升级
	UFUNCTION(BlueprintCallable)
		void LevelUp();
	// 正常时间的生命值、法术值缓慢恢复
	UFUNCTION(BlueprintCallable)
		void Refill();
};
