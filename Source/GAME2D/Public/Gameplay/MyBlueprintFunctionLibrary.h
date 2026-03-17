// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UMG/HUD_All_UI.h"
#include "MyBlueprintFunctionLibrary.generated.h"

class UMyGameInstance;
/**
 * 
 */
UCLASS()
class GAME2D_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/*  获取游戏实例  */
	UFUNCTION(BlueprintPure,  meta = (WorldContext = "WorldContextObject"))
	static UMyGameInstance* GetGameInstanceBase(const UObject* WorldContextObject);
	
	/*  获取玩家控制器  */
	UFUNCTION(BlueprintPure,  meta = (WorldContext = "WorldContextObject"))
	static APlayerController* GetPlayerController(const UObject* WorldContextObject);

	/*  获取全部UI  */
	UFUNCTION(BlueprintPure,  meta = (WorldContext = "WorldContextObject"))
	static UHUD_All_UI* GetHUDAllUI(const UObject* WorldContextObject);

	/*  启用/禁用输入  */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void PlayerMoveController(bool bCanMove,UObject* WorldContextObject);
	
};
