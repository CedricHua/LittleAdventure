// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GAME2D\Public\Manager\EnumManager.h"
#include "StructManager.generated.h"

/**
 * 结构体管理器，用于存储游戏内的所有结构体
 */
class AItemBase;
// 任务表格
USTRUCT(Blueprintable)
struct FTASK_System : public FTableRowBase
{
	GENERATED_BODY()
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ECharacter_Names TargetNPC;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText TaskText;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UDataTable* DialogueToShow;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AActor> TargetActor = nullptr;
};

// 对话表
USTRUCT(Blueprintable)
struct FDIALOGUE : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* PeopleImage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ECharacter_Names Name;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString Text;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bShouldCallEvent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bDialogueIsEnd;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bMissionComplete;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bAutoSave;  // 自动存档
	
};

// 物品结构体
USTRUCT(Blueprintable)
struct FItem_Struct : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AItemBase* ItemClass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString Name;  // 物品名
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString Description;  // 描述
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Index;  // 索引
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* Icon;  // 图标
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Count;  // 当前数量
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Max_Count;  // 最大数量
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool Can_Stack;  // 是否可堆叠
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 EquipIndex;  // 装备索引（仅在使用物品的时候做区分）
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EItem_type Item_Type;  // 物品类型
};

// 存档系统结构体
USTRUCT(Blueprintable)
struct FPlayerSaveData
{
	// 存档时的属性
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SaveHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SaveMP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SaveArmor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 SaveLevel;  // 玩家当前等级
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SaveExp;  // 玩家当前经验
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int SaveMoney;  // 玩家当前金币
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FItem_Struct> SaveItemArr;  // 玩家当前物品数组
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FItem_Struct> SaveEquipArr;  // 玩家当前装备数组
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 SaveMissionIndex;  // 玩家当前大任务
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 SaveTaskIndex;  // 玩家当前小任务
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 SaveKillCnt;  // 玩家当前KillCnt(Level1)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 SaveEquipCnt;  // 玩家当前EquipCnt(Level2)
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MissionSystem")
	ECharacter_Names SaveTargetNPC;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector PlayerLocation;  // 玩家当前位置
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString PlayerEquipWeapon;  // 玩家当前主武器
	
	

};
UCLASS()
class GAME2D_API UStructManager : public UObject
{
	GENERATED_BODY()
	
};
