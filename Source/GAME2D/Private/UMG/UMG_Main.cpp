// Fill out your copyright notice in the Description page of Project Settings.


#include "GAME2D/Public/UMG/UMG_Main.h"
#include "GAME2D/Public/Manager/StructManager.h"
#include "Gameplay/MyBlueprintFunctionLibrary.h"
#include "Gameplay/MyGameInstance.h"

void UUMG_Main::NativePreConstruct()
{
	Super::NativePreConstruct();
	TaskText->SetVisibility(ESlateVisibility::Hidden);
	
	SwordChi->SetVisibility(ESlateVisibility::HitTestInvisible);  // 设置非可命中测试
	Dash->SetVisibility(ESlateVisibility::HitTestInvisible);  // 设置非可命中测试
	
	SwordChi->SetRenderOpacity(0.0f);
	Dash->SetRenderOpacity(0.0f);
}

void UUMG_Main::PlayHideCanvas()
{
	Button_Interact->SetVisibility(ESlateVisibility::HitTestInvisible);  // 设置非可命中测试
	PlayAnimation(HideCanvas);
}

void UUMG_Main::PlayShowCanvas()
{
	Button_Interact->SetVisibility(ESlateVisibility::Visible);  // 设置可命中测试
	PlayAnimation(ShowCanvas);
}

void UUMG_Main::SetTaskText(int32 Index)
{
	/*  设置当前任务提示文本  */
	UMyGameInstance* MyGameInstance = UMyBlueprintFunctionLibrary::GetGameInstanceBase(GetWorld());
	FName RowName = FName(*FString::FromInt(Index));
	FTASK_System *Find = MyGameInstance->CurrentMission->FindRow<FTASK_System>(RowName,TEXT("Context"));
	if (Find)
	{
		TaskText->SetText(Find->TaskText);  // 任务提示文本
		PlayAnimation(TaskTipAnim,0.f,0.f);
		TaskText->SetVisibility(ESlateVisibility::Visible);
	}
}
