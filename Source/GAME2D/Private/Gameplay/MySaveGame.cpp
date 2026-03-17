// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MySaveGame.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "GAS/BaseAttributeSet.h"
#include "Kismet/GameplayStatics.h"

bool UMySaveGame::SaveGame(const FString& SlotName, int32 UserIndex)
{
	return UGameplayStatics::SaveGameToSlot(this, SlotName, UserIndex);
}

bool UMySaveGame::LoadGame(const FString& SlotName, int32 UserIndex)
{
	UMySaveGame* LoadedSave = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
	if (!LoadedSave) return false;
    
	this->SaveData = LoadedSave->SaveData;
	return true;
}

UMySaveGame* UMySaveGame::CreateSaveGameObject()
{
	return Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
}

bool UMySaveGame::QuickSave(FPlayerSaveData SaveData, const FString& SlotName, int32 UserIndex)
{
	UMySaveGame* SaveGame = CreateSaveGameObject();
	if (!SaveGame) return false;
    
	// 设置数据
	SaveGame->SaveData = SaveData;
    
	// 保存
	return UGameplayStatics::SaveGameToSlot(SaveGame, SlotName, UserIndex);
}

bool UMySaveGame::QuickLoad(FPlayerSaveData& OutSaveData, const FString& SlotName, int32 UserIndex)
{
	UMySaveGame* LoadedGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
    
	if (!LoadedGame) return false;
	
	OutSaveData = LoadedGame->SaveData;
	return true;
}


