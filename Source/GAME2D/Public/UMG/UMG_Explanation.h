// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UMG_Explanation.generated.h"

/**
 * 技能说明界面
 */
UCLASS()
class GAME2D_API UUMG_Explanation : public UUserWidget
{
	GENERATED_BODY()
public:
	// 绑定控件&动画
	UPROPERTY(EditAnywhere,meta = (BindWidget))
	UImage* Description_Image = nullptr;
	UPROPERTY(EditAnywhere,meta = (BindWidget))
	UTextBlock* Description_Text = nullptr;
	UPROPERTY(Transient,meta = (BindWidgetAnim))
	UWidgetAnimation* ShowAnim;
	
	void SetImageAndText(UObject* Image,FText Text);

	virtual void NativeConstruct() override;
};
