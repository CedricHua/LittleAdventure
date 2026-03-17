// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG_ItemSlot.h"
#include "Blueprint/UserWidget.h"
#include "GAME2D\Public/Manager/StructManager.h"
#include "UMG_Backpack.generated.h"

/**
 * 
 */
class UUniformGridPanel;
UCLASS()
class GAME2D_API UUMG_Backpack : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;  // 构造函数（一定要加）

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BackpackSystem")
	FString CurrentType = "Prop";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BackPackSytstem",meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> BackpackPanel;  // 物品面板
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BackPackSytstem",meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> EquipPanel;  // 装备面板
	int32 SlotCount = 32;  //背包允许存在格子数量（可以暴露给蓝图然后自己酌情修改）
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BackPackSytstem",meta = (BindWidget))
	TObjectPtr<UUMG_ItemSlot> WeaponSlot;  // Equip_0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BackPackSytstem",meta = (BindWidget))
	TObjectPtr<UUMG_ItemSlot> ArmorSlot;  // Equip_1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BackPackSytstem",meta = (BindWidget))
	TObjectPtr<UUMG_ItemSlot> BuffSlot;  // Equip_2
	
	UPROPERTY()
	UUMG_ItemSlot* ItemSlot;  // 声明SlotUI，这里也要去UClass()外添加class UBackPackSlot

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BackpackSystem")
	TArray<FItem_Struct> BackPackTransfer;  // 用于构造时从GameInstance中复制数组数据
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BackpackSystem")
	TArray<FItem_Struct> EquipTransfer;  // 用于构造时从GameInstance中复制数组数据
	UFUNCTION(BlueprintCallable,Category="BackPackSystem")
	void RefreshBackPack();  //BackPackUI创建时执行
	
	UFUNCTION(BlueprintCallable,Category="BackPackSystem")
	void RefreshEquip(int32 EquipIndex);
};
