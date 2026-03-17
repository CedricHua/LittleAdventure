// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UMG_Counter.generated.h"

/**
 * 
 */
UCLASS()
class GAME2D_API UUMG_Counter : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UTextBlock* Count;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Count_Kill;
};
