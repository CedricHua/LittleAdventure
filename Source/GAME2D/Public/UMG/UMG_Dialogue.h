// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG_Explanation.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Engine/DataTable.h"
#include "Components/TextBlock.h"
#include "UMG_Dialogue.generated.h"

/**
 * 
 */

UCLASS()
class GAME2D_API UUMG_Dialogue : public UUserWidget
{
	GENERATED_BODY()
public:
	// 绑定控件
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UImage> SpeakerImage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UTextBlock> SpeakerName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UTextBlock> SpeakText;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UButton> NextButton;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UDataTable* DialogueDataTable;

	// 绑定动画
	UPROPERTY(Transient,meta = (BindWidgetAnim))
	UWidgetAnimation* TextAnim;

	
	TArray<FName> RowNamesArray;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UPROPERTY()
	int32 RowIndex=0;
	void UpDataDialogue(UDataTable* DataTable, FName DTRowName);

	// 点击事件
	UFUNCTION()
	void OnNextButtonClicked();

	UFUNCTION(BlueprintImplementableEvent,Category="SaveGame")
	void AutoSaveGame();
};
