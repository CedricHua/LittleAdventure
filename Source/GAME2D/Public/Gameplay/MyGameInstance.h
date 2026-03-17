// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAME2D/Public/Manager/StructManager.h"
#include "Engine/GameInstance.h"
#include "Manager/BaseObjectManager.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAME2D_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	// *******任务系统（Begin）*******
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MissionSystem")
	FName CurrentMapName = "MainMap";  // 存放当前地图的名称
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MissionSystem")
	TArray<UDataTable*> MissionLinerList;  // 存放Mission数据表格

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MissionSystem")
	UDataTable* CurrentMission;  // 当前Mission

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MissionSystem")
	int32 MissionIndex = 0;  // Mission表格中的行

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MissionSystem")
	int32 TaskIndex = 1;  // Task表格中的行

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MissionSystem")
	ECharacter_Names TargetNPC;  // 指定目标NPC

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MissionSystem")
	int32 KillCnt = 0; 
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MissionSystem")
	int32 EquipCnt = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MissionSystem")
	bool bShouldCallEvent = true;
	
	// 函数1：用于初始化Mission和Task
	UFUNCTION(BlueprintCallable)
	virtual void Init() override;

	// 函数2：控制Mission顺序
	UFUNCTION(BlueprintCallable,Category="MissionSystem")
	void MissionControl();

	// 函数3：控制Task顺序
	UFUNCTION(BlueprintCallable,Category="MissionSystem")
	void TaskControl();
	// *******任务系统（End）*******


	// *******对象池（Begin）*******
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MissionSystem")
	ABaseObjectManager* BaseObjectManager; // 链接对象池控制器
	// *******对象池（End）*******

	
	// *******背包系统（Begin）*******
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FItem_Struct> BackPack_Array;  // 游戏实例中的背包物品，可全局保存和使用
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FItem_Struct> Equip_Array;  // 玩家装备栏
	// *******背包系统（End）*******


	// ******玩家全局属性（Begin）*******
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerState")
	float PlayerXP = 0.0f;  // 玩家当前总经验值

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerState")
	int32 PlayerLevel = 0;  // 玩家当前等级

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerState")
	int32 PlayerMoney = 0;  // 玩家总金币数
	// ******玩家全局属性（End）*******
};
