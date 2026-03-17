// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UMG/UMG_TargetPointer.h"
#include "UMG/UMG_Dialogue.h"
#include "TaskSystemComp.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME2D_API UTaskSystemComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TaskSystem")
	UDataTable* CurrentTask;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TaskSystem")
	AActor* HitNPC;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TaskSystem")
	int32 MissionIndex;

	UPROPERTY()
	UUMG_TargetPointer* TargetPointer;  // 任务目标指引UI

	UPROPERTY()
	UUMG_Dialogue* Dialogue;  // 对话界面UI  

	UFUNCTION(BlueprintCallable,Category="TaskSystem")
	void SetTaskTipAndTarget();
	
	UFUNCTION(BlueprintCallable,Category="TaskSystem")
	void SetDialogue();

	UFUNCTION(BlueprintCallable,Category="TaskSystem")
	void CallEvent();  // 每个大任务完成之后发生的事件

	void CreateExplanationAndSet();  // 只有在相应事件时调用
	UPROPERTY()
	UUMG_Explanation* UMG_Explanation;
};
