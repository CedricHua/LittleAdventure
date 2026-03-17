// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MyBlueprintFunctionLibrary.h"


#include "Character/BaseCharacter.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/HUD.h"
#include "Gameplay/MyGameInstance.h"
#include "Gameplay/MyPlayerController.h"
#include "UMG/HUD_All_UI.h"      // 需要包含你的HUD_All_UI头文件
#include "UMG/HUD_Player.h"

UHUD_All_UI* UMyBlueprintFunctionLibrary::GetHUDAllUI(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World) return nullptr;
	APlayerController* PC = World->GetFirstPlayerController();
	if (!PC) return nullptr;
	AHUD_Player* HUD = Cast<AHUD_Player>(PC->GetHUD()); 
	if (!HUD) return nullptr;  
	UHUD_All_UI* HUD_All_UI = HUD->HUD_All_UI;
	return HUD_All_UI;
}

UMyGameInstance* UMyBlueprintFunctionLibrary::GetGameInstanceBase(const UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		UE_LOG(LogTemp, Error, TEXT("WorldContextObject is null in GetGameInstanceBase"));
		return nullptr;
	}
    
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get World from WorldContextObject"));
		return nullptr;
	}
    
	UGameInstance* BaseGameInstance = World->GetGameInstance();
	if (!BaseGameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("World has no GameInstance"));
		return nullptr;
	}
    
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(BaseGameInstance);
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is not of type UMyGameInstance"));
		return nullptr;
	}
    
	return GameInstance;
}

APlayerController* UMyBlueprintFunctionLibrary::GetPlayerController(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World) return nullptr;
	APlayerController* PC = Cast<AMyPlayerController>(World->GetFirstPlayerController());
	return PC?PC:nullptr;
}

void UMyBlueprintFunctionLibrary::PlayerMoveController(bool bCanMove, UObject* WorldContextObject)
{
	// 获取世界上下文
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World) return;
	// 获取玩家控制器
	APlayerController* PC = Cast<AMyPlayerController>(World->GetFirstPlayerController());
	if (!PC) return;

	ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(PC->GetPawn());
	
	if (bCanMove)
	{
		PlayerCharacter->EnableInput(PC);
	}
	else
	{
		PlayerCharacter->DisableInput(PC);
	}
	
}
