// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;
/**
 * 
 */

UCLASS()
class GAME2D_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	
	// 增强输入部分
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category =Input)
	UInputMappingContext* InputMappingContext;

public:
	virtual void BeginPlay() override;

	//*********存档系统(GAS)***********

};
