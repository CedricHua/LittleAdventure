// Fill out your copyright notice in the Description page of Project Settings.


#include "GAME2D/Public/TaskSystem/TaskSystemComp.h"
#include "GAME2D/Public/Gameplay/MyGameInstance.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Gameplay/MyBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UMG/HUD_All_UI.h"
#include "UMG/HUD_Player.h"
#include "UMG/UMG_Dialogue.h"

void UTaskSystemComp::SetTaskTipAndTarget()
{
	/*  设置主UI上显示的任务提示，和目标引导UI  */
	// 获取游戏实例
	UMyGameInstance* MyGameInstance = UMyBlueprintFunctionLibrary::GetGameInstanceBase(GetWorld());
	FName RowName = FName(*FString::FromInt(MyGameInstance->TaskIndex));
	FTASK_System *FindRow = MyGameInstance->CurrentMission->FindRow<FTASK_System>(RowName,TEXT("Context"));
	
	// 用于设置任务提示文本
	UHUD_All_UI* HUD_All_UI = UMyBlueprintFunctionLibrary::GetHUDAllUI(GetWorld());
	if (HUD_All_UI) HUD_All_UI->UMG_Main->SetTaskText(MyGameInstance->TaskIndex);
	
	// 用于设置指引UI
	APlayerController*PC = UMyBlueprintFunctionLibrary::GetPlayerController(this);
	if (!PC) return;
	TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUMG_TargetPointer>(nullptr,TEXT("/Game/System/TaskSystem/BluePrints/UMG_TargetPointer.UMG_TargetPointer_C"));
	TargetPointer = CreateWidget<UUMG_TargetPointer>(PC,WidgetClass);
	if (!TargetPointer) return;
	if (FindRow->TargetActor != nullptr)  // !!!
	{
		TargetPointer -> TargetNPC = UGameplayStatics::GetActorOfClass(this,FindRow->TargetActor);
		TargetPointer->AddToViewport();
	}
}

void UTaskSystemComp::SetDialogue()
{
	/*  显示对话框  */

	if (!GetWorld()) return;
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FName RowName = FName(*FString::FromInt(MyGameInstance->TaskIndex));
	FTASK_System *FindRow = MyGameInstance->CurrentMission->FindRow<FTASK_System>(RowName,TEXT("Context"));

	APlayerController*OwningPlayer = GetWorld()->GetFirstPlayerController();
	TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUMG_Dialogue>(nullptr,TEXT("/Game/System/TaskSystem/BluePrints/UMG_Dialogue.UMG_Dialogue_C"));

	Dialogue = CreateWidget<UUMG_Dialogue>(OwningPlayer,WidgetClass);
	Dialogue->DialogueDataTable = FindRow->DialogueToShow;
	Dialogue->AddToViewport();

	
	OwningPlayer->bShowMouseCursor = true;
}


// 响应事件
void UTaskSystemComp::CallEvent()
{
    // 1. 获取GameInstance
	UMyGameInstance* MyGameInstance = UMyBlueprintFunctionLibrary::GetGameInstanceBase(this);  //!!!
    if (!MyGameInstance) return;
	if (UGameplayStatics::GetCurrentLevelName(this) == TEXT("MnueUIMap")) return;  // 菜单界面不处理
    switch (MyGameInstance->MissionIndex)
    {
    case 0:
        CreateExplanationAndSet();
    	MyGameInstance->bShouldCallEvent = false;
        break;
    case 3:
    	CreateExplanationAndSet();
    	MyGameInstance->bShouldCallEvent = false;
        break;
    }
}

void UTaskSystemComp::CreateExplanationAndSet()
{
	// 1. 获取GameInstance
	UMyGameInstance* MyGameInstance = UMyBlueprintFunctionLibrary::GetGameInstanceBase(GetWorld());
	if (!MyGameInstance) return;

	// 2. 获取PlayerController
	APlayerController* PC = UMyBlueprintFunctionLibrary::GetPlayerController(GetWorld());
	if (!PC) return;

	// 3. 设置输入模式(UI only)
	PC->SetShowMouseCursor(true);
	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(nullptr);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PC->SetInputMode(InputMode);

	// 4. 加载并创建Widget
	TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/System/TaskSystem/BluePrints/UMG_Explanation.UMG_Explanation_C"));
	if (!WidgetClass) return;

	UMG_Explanation = CreateWidget<UUMG_Explanation>(PC, WidgetClass);
	if (!UMG_Explanation) return;
	UMG_Explanation->AddToViewport();
	UMG_Explanation->SetVisibility(ESlateVisibility::Visible);

	// 5. 根据任务索引处理
	UObject* Image = nullptr;
	FString TextString;
	switch (MyGameInstance->MissionIndex)
	{
	case 0:
		Image = LoadObject<UTexture2D>(nullptr, TEXT("/Game/UMG/Assets/D_Attack"));
		TextString = TEXT("玩家初始技能，点击“攻击”按钮即可攻击，可对敌人造成少量伤害");
		break;
	case 3:
		if (MyGameInstance->TaskIndex == 1)
		{
			Image = LoadObject<UTexture2D>(nullptr, TEXT("/Game/UMG/Assets/D_Sword_Chi"));
			TextString = TEXT("获得技能“剑气”，按下按钮即可释放，可对敌人造成高额伤害，同时消耗少量魔法值");
			AHUD_Player* HUD = Cast<AHUD_Player>(PC->GetHUD());
			if (HUD && HUD->HUD_All_UI && HUD->HUD_All_UI->UMG_Main && HUD->HUD_All_UI->UMG_Main->SwordChi)
			{
				HUD->HUD_All_UI->UMG_Main->SwordChi->SetRenderOpacity(1.0f);  // 显示剑气按钮
				HUD->HUD_All_UI->UMG_Main->SwordChi->SetVisibility(ESlateVisibility::Visible);  // 设置可命中测试
			}
			// 更新任务提示
			ABaseCharacter* Player = Cast<ABaseCharacter>(PC->GetPawn());
			if (Player && Player->TaskSystemComp)
			{
				Player->TaskSystemComp->SetTaskTipAndTarget();
			}
			
		}
		else if (MyGameInstance->TaskIndex == 4)
		{
			Image = LoadObject<UTexture2D>(nullptr, TEXT("/Game/UMG/Assets/D_Dash"));
			TextString = TEXT("获得技能“闪身”，按下按钮即可释放，朝移动方向位移一段距离，同时消耗耐力");
			AHUD_Player* HUD = Cast<AHUD_Player>(PC->GetHUD());
			if (HUD && HUD->HUD_All_UI && HUD->HUD_All_UI->UMG_Main && HUD->HUD_All_UI->UMG_Main->SwordChi)
			{
				HUD->HUD_All_UI->UMG_Main->Dash->SetRenderOpacity(1.0f);  // 显示闪身按钮
				HUD->HUD_All_UI->UMG_Main->Dash->SetVisibility(ESlateVisibility::Visible);  // 设置可命中测试
			}
		}
		break;

	}
	// 6. 调用Widget函数
	FText Text = FText::FromString(TextString);
	UMG_Explanation->SetImageAndText(Image, Text);
}

