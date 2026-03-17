// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "PaperZDCharacter.h"
#include "GAS/BaseAbilitySystemComponent.h"
#include "TaskSystem/TaskSystemComp.h"
#include "UMG/UMG_Backpack.h"
#include "BaseCharacter.generated.h"

/**
	基础角色，用于玩家和敌人继承的父类
 */
class UBackpackComponent;
class AItemBase;
class UAbilitySystemComponent;
class UInputMappingContext;
class UInputAction;
class FString;
class FCharacterMovementComponent;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueChangedEvent, float ,NewVal);

UCLASS()
class GAME2D_API ABaseCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
public:
	ABaseCharacter();
	
	// *************增强输入部分
	// Move Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* OpenBPAction;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;  
	FCharacterMovementComponent* MovementComponent;

	// *************背包部分
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "BackPackSystem")
	UBackpackComponent* BackpackComponent;  // 背包组件

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BackpackSystem")
	AItemBase* FocusedItem;  // 用于标记我们按E拾取的是哪个物品  需要class AItemBase;标记


	
	// *************GAS部分
	UPROPERTY(BlueprintReadWrite,Category="GAS")
	UBaseAbilitySystemComponent* MyASC;
	
	UPROPERTY(BlueprintAssignable,Category="GAS")
	FOnValueChangedEvent HPChangeEvent; // 血量变化多播委托

	UPROPERTY(BlueprintAssignable,Category="GAS")
	FOnValueChangedEvent MPChangeEvent; // 蓝量变化

	UPROPERTY(BlueprintAssignable,Category="GAS")
	FOnValueChangedEvent StrengthChangeEvent; // 体力变化

	UPROPERTY(BlueprintAssignable,Category="GAS")
	FOnValueChangedEvent ArmorChangeEvent; 


	// 属性变化时的广播
	void OnHPAttributeChanged(const FOnAttributeChangeData &Data);
	void OnMPAttributeChanged(const FOnAttributeChangeData &Data);
	void OnStrengthAttributeChanged(const FOnAttributeChangeData &Data);
	void OnArmorAttributeChanged(const FOnAttributeChangeData &Data);

	UFUNCTION(BlueprintCallable,Category="GAS")
	void ActivateTag(UAbilitySystemComponent* ASC,FGameplayTag Tag);
	UFUNCTION(BlueprintCallable,Category="GAS")
	void DeactivateTag(UAbilitySystemComponent* ASC,FGameplayTag Tag);

	// *************任务系统部分
	UPROPERTY(BlueprintReadWrite,Category="TaskSystem")
	UTaskSystemComp* TaskSystemComp;
	
	// *************工具函数部分
	// 方向处理（Player）
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Direction")
	float Dir_X;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Direction")
	float Dir_Y;
	
	
	// 处理对象池
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ObjectPool")
	float Vel_X;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ObjectPool")
	float Vel_Y;
	
	
	void SetVel();  // 每帧记录角色当前的速度方向
	UFUNCTION(BlueprintCallable,Category="ObjectPool")
	float GetAngle(); // 通过速度方向获取生成物的旋转角

	
protected:
	// Called for movement input 
	void Move(const FInputActionValue& Value);
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	
	//碰撞检测应用伤害
	UFUNCTION(BlueprintCallable,Category="GAS")
	ACharacter* SpawnAndHit(float X, float Y);

public:
	UFUNCTION(BlueprintCallable,Category="PlayerState")
	void GetExperience(float inExperience,TSubclassOf<UGameplayEffect> LevelUpEffectClass);
};
