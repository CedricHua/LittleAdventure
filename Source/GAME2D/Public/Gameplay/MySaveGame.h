// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Manager/StructManager.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class GAME2D_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	FPlayerSaveData SaveData;  // 存档结构体

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	bool SaveGame(const FString& SlotName, int32 UserIndex = 0);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	bool LoadGame(const FString& SlotName, int32 UserIndex = 0);
	
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	static UMySaveGame* CreateSaveGameObject();  // 创建SaveGame对象

	// 蓝图调用快速保存数据
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	static bool QuickSave(FPlayerSaveData InSaveData, const FString& SlotName = "SaveSlot", int32 UserIndex = 0);

	// 蓝图调用快速加载数据
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	static bool QuickLoad(FPlayerSaveData& OutSaveData, const FString& SlotName = "SaveSlot", int32 UserIndex = 0);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData HP;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MP;
	
};
