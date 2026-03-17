// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/UMG_Explanation.h"
#include "Components/TextBlock.h"

void UUMG_Explanation::NativeConstruct()
{
	Super::NativeConstruct();
	PlayAnimation(ShowAnim);
}

void UUMG_Explanation::SetImageAndText(UObject* Image,FText Text)
{
	// 将UObject强制转换为UTexture2D                           **UTexture2D类型为UObject的子类，可以进行转换
	if (UTexture2D* Texture = Cast<UTexture2D>(Image))
	{
		Description_Image->SetBrushFromTexture(Texture);  	// 设置纹理到Image控件  !!!
		Description_Text->SetText(Text);
	}
	
}