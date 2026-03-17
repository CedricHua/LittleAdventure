// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG_TargetPointer.generated.h"

/**
 * 
 */
UCLASS()
class GAME2D_API UUMG_TargetPointer : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AActor* TargetNPC = nullptr;
	
	
};
