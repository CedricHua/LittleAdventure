// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/UMG_Dialogue.h"


#include "Character/BaseCharacter.h"
#include "Gameplay/MyBlueprintFunctionLibrary.h"
#include "Gameplay/MyGameInstance.h"
#include "Manager/StructManager.h"
#include "UMG/HUD_Player.h"


void UUMG_Dialogue::NativePreConstruct()
{
	/*  事件预构造  */
	Super::NativePreConstruct();
	UHUD_All_UI* HUD_All_UI = UMyBlueprintFunctionLibrary::GetHUDAllUI(this);
	if (!HUD_All_UI) return;
	HUD_All_UI->UMG_Main->PlayHideCanvas();  // 播放动画用于隐藏MainUI  // !!!
	UMyBlueprintFunctionLibrary::PlayerMoveController(false,this);  // 禁用玩家输入
	if (!DialogueDataTable) return;
	RowNamesArray = DialogueDataTable->GetRowNames();
	PlayAnimation(TextAnim,0.f,0.f);
}

void UUMG_Dialogue::NativeConstruct()
{
	/*  构造事件  */
	Super::NativeConstruct();
	
	// 绑定按钮点击事件
	NextButton->OnClicked.AddDynamic(this, &UUMG_Dialogue::OnNextButtonClicked);
	//初始调用一次
	UpDataDialogue(this->DialogueDataTable,this->RowNamesArray[RowIndex]);
	RowIndex++;
}

void UUMG_Dialogue::UpDataDialogue(UDataTable* DataTable, FName DTRowName)
{
	FDIALOGUE* FindRow = DataTable->FindRow<FDIALOGUE>(DTRowName,TEXT("Context"));

	// 分别设置名字，说话内容和图片
	this->SpeakerName->SetText(StaticEnum<ECharacter_Names>()->GetDisplayNameTextByValue((int64)FindRow->Name));
	this->SpeakText->SetText(FText::FromString(FindRow->Text));
	this->SpeakerImage->SetBrushFromTexture(FindRow->PeopleImage);
}

void UUMG_Dialogue::OnNextButtonClicked()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FDIALOGUE* FindRow = DialogueDataTable->FindRow<FDIALOGUE>(RowNamesArray[RowIndex], TEXT("Context"));
	UpDataDialogue(DialogueDataTable, RowNamesArray[RowIndex]);

	// 如果不是最后一行，递增索引并返回
	if (!FindRow->bDialogueIsEnd)
	{
		RowIndex++;
		return;
	}

	// 如果是最后一行，开始关闭流程
	NextButton->SetVisibility(ESlateVisibility::Hidden);
	
	// 使用定时器处理延迟关闭
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		[this, GameInstance, FindRow]() 
		{
			// 1. 显示主UI
			UHUD_All_UI* HUD_All_UI = UMyBlueprintFunctionLibrary::GetHUDAllUI(this);
			if (HUD_All_UI && HUD_All_UI->UMG_Main)
			{
				HUD_All_UI->UMG_Main->PlayShowCanvas();
			}
			
			// 2. 处理任务逻辑
			if (FindRow->bMissionComplete)
			{
				if (GameInstance)
				{
					GameInstance->MissionIndex++;
					GameInstance->TaskIndex = 1;
					
					if (HUD_All_UI && HUD_All_UI->UMG_Main && HUD_All_UI->UMG_Main->TaskText)
					{
						HUD_All_UI->UMG_Main->TaskText->SetVisibility(ESlateVisibility::Hidden);
					}
					
					if (GameInstance->MissionIndex < GameInstance->MissionLinerList.Num())
					{
						GameInstance->MissionControl();
					}
					
					if (FindRow->bAutoSave)
					{
						AutoSaveGame();
					}
				}
			}
			else
			{
				if (GameInstance)
				{
					GameInstance->TaskIndex++;
					GameInstance->TaskControl();
					if (FindRow->bAutoSave)
					{
						AutoSaveGame();
					}
					// 更新任务提示
					APlayerController* PC = UMyBlueprintFunctionLibrary::GetPlayerController(this);
					if (PC)
					{
						ABaseCharacter* Player = Cast<ABaseCharacter>(PC->GetPawn());
						if (Player && Player->TaskSystemComp)
						{
							Player->TaskSystemComp->SetTaskTipAndTarget();
						}
					}
				}
			}
			
			// 3. 处理事件调用
			if (FindRow->bShouldCallEvent)
			{
				APlayerController* PC = UMyBlueprintFunctionLibrary::GetPlayerController(this);
				if (PC)
				{
					ABaseCharacter* Player = Cast<ABaseCharacter>(PC->GetPawn());
					if (Player && Player->TaskSystemComp)
					{
						Player->TaskSystemComp->CallEvent();
					}
				}
			}
			
			// 4. 恢复玩家控制并移除UI
			UMyBlueprintFunctionLibrary::PlayerMoveController(true, this);
			RemoveFromParent();
		},
		1.0f,  // 延迟1秒
		false  // 不循环，只执行一次
	);
}


