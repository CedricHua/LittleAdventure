// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "TaskSystemComp.h"
#include "BaseNPC.generated.h"

/**
 * 
 */
UCLASS()
class GAME2D_API ABaseNPC : public APaperZDCharacter
{
	GENERATED_BODY()
public:
	ABaseNPC();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName NPC_Name;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "BackPackSystem")
	UTaskSystemComp* TaskSystemComp;  // 背包组件

	void SetNPC();

};
