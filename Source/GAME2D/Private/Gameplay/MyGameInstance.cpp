// Fill out your copyright notice in the Description page of Project Settings.


#include "GAME2D/Public/Gameplay/MyGameInstance.h"


//********任务系统********




void UMyGameInstance::Init()
{
	Super::Init();
	Equip_Array.Init(FItem_Struct(), 3);
	MissionControl();
	TaskControl();
}

void UMyGameInstance::MissionControl()
{
	/* 只有Task走到最后的时候才会调用这个函数 */
	CurrentMission = MissionLinerList[MissionIndex];  
	TaskControl();
}

void UMyGameInstance::TaskControl()
{
	if (!CurrentMission) return;
	FName RowName = FName(*FString::FromInt(TaskIndex));
	FTASK_System* FindRow = CurrentMission->FindRow<FTASK_System>(RowName,TEXT("Context"));
	if (FindRow)
	{
		// 根据Task赋予其指定的NPC
		TargetNPC = FindRow->TargetNPC;
	}
}
