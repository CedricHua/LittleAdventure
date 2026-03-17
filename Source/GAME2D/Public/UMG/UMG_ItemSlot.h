// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BackpackSystem/ItemBase.h"
#include "Blueprint/UserWidget.h"
#include "UMG_ItemSlot.generated.h"

/**
 * 
 */
class UTexture2D;
class UTextBlock;
class UImage;

UCLASS()
class GAME2D_API UUMG_ItemSlot : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	// 用于操作的控件
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "BackPackSystem" , meta = (BindWidget))
	UImage* SlotImage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "BackPackSystem" , meta = (BindWidget))
	UTextBlock* Number_Text;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "BackPackSystem")
	int32 Index = -1;  // 外部传入，如果有东西就是对应物品在数组中的索引，如果没有就是-1
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "BackPackSystem")
	int32 Number = 0;  // 外部传入，物品数量
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "BackPackSystem")
	UTexture2D* Image;  // 外部传入，物品图标
	
	
	void SetSlot();  // 设置格子内容
};
