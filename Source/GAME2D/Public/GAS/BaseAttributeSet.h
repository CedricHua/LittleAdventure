// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

/*
	设置与GAS有关的角色属性，如玩家的血量，蓝量，敌人的血量等等
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
UCLASS()
class GAME2D_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseAttributeSet")
	FGameplayAttributeData HP;  // 血量
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet,HP);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseAttributeSet")
	FGameplayAttributeData MAX_HP;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet,MAX_HP);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseAttributeSet")
	FGameplayAttributeData MP;  // 蓝量
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet,MP);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseAttributeSet")
	FGameplayAttributeData MAX_MP;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet,MAX_MP);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseAttributeSet")
	FGameplayAttributeData Strength;  // 体力
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet,Strength);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseAttributeSet")
	FGameplayAttributeData MAX_Strength;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet,MAX_Strength);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseAttributeSet")
	FGameplayAttributeData WalkSpeed;  // 玩家移速
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet,WalkSpeed);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseAttributeSet")
	FGameplayAttributeData Armor;  // 护甲值
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet,Armor);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseAttributeSet")
	FGameplayAttributeData MAX_Armor;  
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet,MAX_Armor);
	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;


};
