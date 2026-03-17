// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAME2D/Public/UMG/UMG_Counter.h"
#include "GAME2D/Public/UMG/UMG_Main.h"
#include "Blueprint/UserWidget.h"
#include "HUD_All_UI.generated.h"

/**
 * 
 */
UCLASS()
class GAME2D_API UHUD_All_UI : public UUserWidget
{
	GENERATED_BODY()
public:
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UUMG_Counter* UMG_Counter = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UUMG_Main* UMG_Main = nullptr;
	
	UPROPERTY(Transient,meta = (BindWidgetAnim))
	UWidgetAnimation* ShowAnim;
	
};
