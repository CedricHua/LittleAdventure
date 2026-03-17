// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Actor.h"
#include "Manager/StructManager.h"
#include "ItemBase.generated.h"

class UGameplayAbility;
class USphereComponent;

UCLASS()
class GAME2D_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BackPackSystem")
	FItem_Struct CurrentItemState;  // 存储当前物品的所有信息
    
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Comp")
	USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="GAS")
	FGameplayTagContainer SelfItemTag;  // 自身标签

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	TSubclassOf<UGameplayAbility> ConsumableAbility;  // 使用时对应的GA
	
	UFUNCTION(BlueprintCallable,Category="GAS")
	void UseItem(AActor* User,int32 SlotIndex);

	UFUNCTION(BlueprintCallable,Category="GAS")
	void UseWeapon(AActor* User,int32 BackPackArrIndex,int32 SelfEquipIndex);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable,Category="GAS")
	void WeaponUseCallBack();  // 武器类使用物品的回调（应用GA/UI切换，在蓝图中写）
};
