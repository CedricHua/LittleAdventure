// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseEnemy.generated.h"

/**
 * 要重写的内容有：1.攻击方式，还是按照原来的速度方向去生成碰撞检测 2.对象池相关
 * 
 */

UENUM(BlueprintType)
enum class EActorState : uint8
{
	Active     UMETA(DisplayName = "Active"),
	Recycle      UMETA(DisplayName = "Recycle")
};

UCLASS()
class GAME2D_API ABaseEnemy : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	// ********对象池
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EActorState CurrentState;   // 敌人当前状态

	
	UFUNCTION(BlueprintCallable)
	void InitSelf();
	UFUNCTION(BlueprintCallable)
	void RecycleSelf();
	
	// 方向处理（Player）
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Direction")
	float E_Dir_X;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Direction")
	float E_Dir_Y;
	void SetCurrentDir(float X, float Y);  // 敌人的（Dir_X,Dir_Y）单独计算，因为没有方向键输入
	UFUNCTION(BlueprintCallable,Category="GAS")
	ACharacter* E_SpawnAndHit(float X, float Y);
};
