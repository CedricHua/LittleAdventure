// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnumManager.generated.h"

/**
 * 枚举管理器，用于存放游戏内的所有枚举类型
 */

// NPC名字
UENUM(Blueprintable)
enum class ECharacter_Names : uint8
{
	Alex UMETA(DisplayName = "Alex"),
	EVA UMETA(DisplayName = "EVA"),
	Edric UMETA(DisplayName = "Edric"),
	Leofwin UMETA(DisplayName = "Leofwin"),
	Gare UMETA(DisplayName = "Gare"),
	Baldwin UMETA(DisplayName = "Baldwin"),
	Ewan UMETA(DisplayName = "Ewan"),
	Max UMETA(DisplayName = "Max"),
	GameOver UMETA(DisplayName = "GameOver"),
	Null UMETA(DisplayName = "NULL"),

};

// 物品类型
UENUM(Blueprintable)
enum class EItem_type : uint8
{
	Weapon UMETA(DisplayName = "Weapon"),
	Prop UMETA(DisplayName = "Prop"),
	Food UMETA(DisplayName = "Food")
};
UCLASS()
class GAME2D_API UEnumManager : public UObject
{
	GENERATED_BODY()
	
};
