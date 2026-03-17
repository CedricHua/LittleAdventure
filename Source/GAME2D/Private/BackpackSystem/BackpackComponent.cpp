// Fill out your copyright notice in the Description page of Project Settings.


#include "BackpackSystem/BackpackComponent.h"
#include "Gameplay/MyBlueprintFunctionLibrary.h"
#include "Gameplay/MyGameInstance.h"
#include "Gameplay/MyPlayerController.h"
#include "UMG/BlueprintUIInterface.h"

// Sets default values for this component's properties
UBackpackComponent::UBackpackComponent()
{
	
}

void UBackpackComponent::AddItem(FItem_Struct NewItem,AItemBase* ItemRef)
{
	/*  向物品数组中添加  */
	
	UMyGameInstance* MyGameInstance=UMyBlueprintFunctionLibrary::GetGameInstanceBase(this);
	TArray<FItem_Struct>& BackpackArray = MyGameInstance->BackPack_Array;
    
	// 查找背包中是否有相同名称的物品
	for (auto& Item : BackpackArray)
	{
		if (Item.Name == NewItem.Name && Item.Can_Stack && Item.Count < Item.Max_Count)
		{
			Item.ItemClass = ItemRef;
			Item.Count += NewItem.Count;
			return;
		}
	}
	// 如果没有找到匹配项或者物品不可堆叠，则作为新物品添加
	NewItem.Index = BackpackArray.Num();
	NewItem.ItemClass = ItemRef;
	BackpackArray.Add(NewItem);
}

void UBackpackComponent::ReduceItem(int32 SlotIndex)
{
	if (!IsValid(GetWorld())) return;
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	APlayerController* PC = UMyBlueprintFunctionLibrary::GetPlayerController(this);
	TArray<FItem_Struct>& BackPackArray = MyGameInstance->BackPack_Array; // 通过引用直接使用 GameInstance 的数组

	// 边界检查
	if (SlotIndex < 0 || SlotIndex >= BackPackArray.Num()) return;
	if (BackPackArray.Num() > 0)
	{
		// 修改原始数组
		BackPackArray[SlotIndex].Count--;  // 数量减1
		// 如果没了，就把它移除
		if (BackPackArray[SlotIndex].Count <= 0) BackPackArray.RemoveAt(SlotIndex);

		TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUserWidget>(nullptr,TEXT("/Game/System/BackPackSystem/Blueprints/UI/UMG_Backpack.UMG_Backpack_C"));
		WidgetToNotify = CreateWidget(PC,WidgetClass);
	}
}




