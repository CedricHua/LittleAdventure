// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/UMG_Backpack.h"

#include "Components/UniformGridPanel.h"
#include "Gameplay/MyBlueprintFunctionLibrary.h"
#include "Gameplay/MyGameInstance.h"

void UUMG_Backpack::NativeConstruct()
{
	Super::NativeConstruct();
	RefreshBackPack();
}

void UUMG_Backpack::RefreshBackPack()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	BackPackTransfer = GameInstance->BackPack_Array;
	EquipTransfer= GameInstance->Equip_Array;
	/* UI每次构造时调用函数刷新背包内所有的格子 */
	APlayerController*OwningPlayer = UMyBlueprintFunctionLibrary::GetPlayerController(this);
	// 这个路径时BackPackSlot的，具体可以看模板中是哪个类就是谁的路径
	TSubclassOf<UUMG_ItemSlot> WidgetClass = LoadClass<UUMG_ItemSlot>(nullptr, TEXT("/Game/System/BackPackSystem/Blueprints/UI/UMG_ItemSlot.UMG_ItemSlot_C"));

	BackpackPanel->ClearChildren();  // 首先要清除子项
	TArray<int32> matchingIndices;  // 存储匹配类型的物品在原始数组中的索引
	for (int32 i = 0; i < BackPackTransfer.Num(); i++)
	{
		if (UEnum::GetDisplayValueAsText(BackPackTransfer[i].Item_Type).ToString() == this->CurrentType)
		{
			matchingIndices.Add(i);
		}
	}
	// 创建物品栏格子
	for (int32 i = 0; i < SlotCount; i++)
	{
		ItemSlot = CreateWidget<UUMG_ItemSlot>(OwningPlayer, WidgetClass);
		if (i < matchingIndices.Num())  // 如果还有匹配的物品
		{
			int32 originalIndex = matchingIndices[i];  // 获取原始数组索引
			ItemSlot->Image = BackPackTransfer[originalIndex].Icon;
			ItemSlot->Index = originalIndex;  // 保存实际索引
			ItemSlot->Number = BackPackTransfer[originalIndex].Count;
			ItemSlot->SetSlot();
		}
		BackpackPanel->AddChildToUniformGrid(ItemSlot,(i/8),(i%8));
	}
}

void UUMG_Backpack::RefreshEquip(TArray<FItem_Struct> ItemArr,int32 EquipIndex)
{
	// UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	// EquipTransfer= GameInstance->Equip_Array;
	EquipTransfer = ItemArr;
	switch (EquipIndex)
	{
	case 0:
		WeaponSlot->Image = EquipTransfer[EquipIndex].Icon;
		WeaponSlot->SetSlot();
		break;
	case 1:
		ArmorSlot->Image = EquipTransfer[EquipIndex].Icon;
		ArmorSlot->SetSlot();
		break;
	case 2:
		BuffSlot->Image = EquipTransfer[EquipIndex].Icon;
		BuffSlot->SetSlot();
		break;
	}
}
