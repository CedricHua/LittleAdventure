// Fill out your copyright notice in the Description page of Project Settings.


#include "GAME2D/Public/UMG/HUD_Player.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GAME2D/Public/Gameplay/MyGameInstance.h"
#include "GAME2D/Public/UMG/HUD_All_UI.h"
#include "Gameplay/MyBlueprintFunctionLibrary.h"

void AHUD_Player::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PC = UMyBlueprintFunctionLibrary::GetPlayerController(this); 
	TSubclassOf<UUserWidget> WidgetClass = LoadClass<UHUD_All_UI>(nullptr,TEXT("/Game/UMG/MyHUD_All_UI.MyHUD_All_UI_C"));
	
	HUD_All_UI = CreateWidget<UHUD_All_UI>(PC,WidgetClass);
	if (!HUD_All_UI) return;  // HUD_All_UI检查

	UMyGameInstance* MyGameInstance = UMyBlueprintFunctionLibrary::GetGameInstanceBase(GetWorld());
	if (!MyGameInstance) return;
	if (UGameplayStatics::GetCurrentLevelName(this) == TEXT("MnueUIMap")) return;  // 菜单界面不处理
	HUD_All_UI->AddToViewport();
	UpdateUI();

}


void AHUD_Player::UpdateUI()
{
	/*  用于管控UI在某些特定地图上的显隐  */
	FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
    
	if (LevelName.Equals(TEXT("MainMap"), ESearchCase::IgnoreCase))
	{
		HUD_All_UI->UMG_Counter->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (LevelName.Equals(TEXT("Level1_Forest"), ESearchCase::IgnoreCase))
	{
		HUD_All_UI->UMG_Counter->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		HUD_All_UI->UMG_Counter->SetVisibility(ESlateVisibility::Hidden);
	}
}
