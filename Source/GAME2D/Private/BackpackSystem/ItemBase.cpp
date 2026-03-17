// Fill out your copyright notice in the Description page of Project Settings.



#include "BackpackSystem/ItemBase.h"

#include "BackpackSystem/BackpackComponent.h"
#include "GAME2D/Public/GAS/BaseGameplayAbility.h"  // 必须包含自定义Ability类的头文件
#include "Character/BaseCharacter.h"
#include "Components/SphereComponent.h"
#include "Gameplay/MyBlueprintFunctionLibrary.h"
#include "Gameplay/MyGameInstance.h"
#include "GAS/BaseAttributeSet.h"

// Sets default values
AItemBase::AItemBase()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = SphereComp;  // 设置根组件


}

// 使用物品
void AItemBase::UseItem(AActor* User,int32 SlotIndex)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(User);
	if (Player)
	{
		Player->BackpackComponent->ReduceItem(SlotIndex);

		UBaseAbilitySystemComponent*OwnerASC=Player->MyASC;
		if (OwnerASC)
		{
			TSubclassOf<UGameplayAbility> AbilityClass = ConsumableAbility;
			FGameplayAbilitySpec* Spec = OwnerASC->FindAbilitySpecFromClass(AbilityClass);
			if (Spec)
			{
				// 保存要添加的标签
				FGameplayTag ItemTag = SelfItemTag.GetByIndex(0);
				// 先移除旧标签
				Spec->DynamicAbilityTags.RemoveTag(ItemTag);
				// 添加当前物品标签
				Spec->DynamicAbilityTags.AddTag(ItemTag);
				// 尝试激活能力
				bool bActivated = OwnerASC->TryActivateAbilityByClass(AbilityClass);
				// 激活后立即清除标签，避免影响下次使用
				if (bActivated)
				{
					Spec->DynamicAbilityTags.RemoveTag(ItemTag);
				}
			}
		}
	}
}

void AItemBase::UseWeapon(AActor* User,int32 BackPackArrIndex,int32 SelfEquipIndex)
{
	/*  武器类使用物品逻辑单独处理  */
	
	UMyGameInstance* MyGameInstance = UMyBlueprintFunctionLibrary::GetGameInstanceBase(this);
	if (!MyGameInstance) return;
    
	ABaseCharacter* Player = Cast<ABaseCharacter>(User);
	if (!Player) return;
    
	/* 背包组件检查 */
	if (!Player->BackpackComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("BackpackComponent is null!"));
		return;
	}
    
	TArray<FItem_Struct>& BackPackArray = MyGameInstance->BackPack_Array;
	TArray<FItem_Struct>& EquipArray = MyGameInstance->Equip_Array;

    
	if (EquipArray[SelfEquipIndex].Count < 1)
	{
		EquipArray[SelfEquipIndex] = BackPackArray[BackPackArrIndex];
		Player->BackpackComponent->ReduceItem(BackPackArrIndex);
	}
	else
	{
		FItem_Struct Temp = EquipArray[SelfEquipIndex];
		EquipArray[SelfEquipIndex] = BackPackArray[BackPackArrIndex];
		BackPackArray[BackPackArrIndex] = Temp;
	}
	WeaponUseCallBack();  // 装备武器后的回调
}







