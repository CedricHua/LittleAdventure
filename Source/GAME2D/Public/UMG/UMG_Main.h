// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "UMG_Main.generated.h"

/**
 * 
 */

UCLASS()
class GAME2D_API UUMG_Main : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativePreConstruct() override;
	// 绑定控件
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UProgressBar> Bar_Armor;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UProgressBar> Bar_Strength;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UProgressBar> Bar_Experience;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UProgressBar> Bar_HP;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UProgressBar> Bar_MP;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UButton> SwordAttack;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UButton> SwordChi;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
    TObjectPtr<UButton> Dash;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UButton> Button_Interact;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UImage> AttackIcon;
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UTextBlock> TaskText;

	// 绑定UI动画
	UPROPERTY(Transient,meta = (BindWidgetAnim))
	UWidgetAnimation* TaskTipAnim;
	
	UPROPERTY(Transient,meta = (BindWidgetAnim))
	UWidgetAnimation* HideCanvas;
	
	UPROPERTY(Transient,meta = (BindWidgetAnim))
	UWidgetAnimation* ShowCanvas;

	// 控制播放隐藏&显示整个UI
	UFUNCTION()
	void PlayHideCanvas();
	UFUNCTION()
	void PlayShowCanvas();

	// 用于更新上方任务提示文本（由GameInstance里的TaskIndex定位）
	UFUNCTION()
	void SetTaskText(int32 Index);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void ExchangeAtkIcon(UTexture2D* InImage);
};
