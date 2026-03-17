// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/UMG_ItemSlot.h"
#include <string>
#include "Components/Image.h"
#include "Styling/SlateBrush.h"
#include "Math/Color.h"
#include "Components/TextBlock.h"

void UUMG_ItemSlot::NativeConstruct()
{
	Super::NativeConstruct();


}

void UUMG_ItemSlot::SetSlot()
{

    /* 主要去渲染格子内容，通过Number判断 */
    if (Number > 1)
    {
        // 需要显示出右下角数字
        Number_Text->SetText(FText::FromString(FString(std::to_string(Number).c_str())));
        Number_Text->SetOpacity(1.0f);
    }
    else
    {
       // 不需要显示数字，直接隐藏掉
       Number_Text->SetOpacity(0.0f);
    }
    // 将Texture2D类型传递给自定义的Image组件去渲染
	FSlateBrush InBrush;
	InBrush.SetResourceObject(Image);
	SlotImage->SetBrush(InBrush);
	FLinearColor F = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	SlotImage->SetColorAndOpacity(F);
	

}
