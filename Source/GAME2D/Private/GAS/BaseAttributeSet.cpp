// Fill out your copyright notice in the Description page of Project Settings.


#include "GAME2D/Public/GAS/BaseAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/MyBlueprintFunctionLibrary.h"



void UBaseAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetHPAttribute())
	{
		SetHP(FMath::Clamp(GetHP(),0.0,GetMAX_HP()));
	}
	else if (Data.EvaluatedData.Attribute == GetMPAttribute())
	{
		SetMP(FMath::Clamp(GetMP(),0.0,GetMAX_MP()));
	}
	else if (Data.EvaluatedData.Attribute == GetStrengthAttribute())
	{
		SetStrength(FMath::Clamp(GetStrength(),0.0,GetMAX_Strength()));
	}
	else if (Data.EvaluatedData.Attribute == GetArmorAttribute())
	{
		SetArmor(FMath::Clamp(GetArmor(),0.0,GetMAX_Armor()));
	}
	else if (Data.EvaluatedData.Attribute == GetWalkSpeedAttribute())
	{
		APlayerController*PC = UMyBlueprintFunctionLibrary::GetPlayerController(GetWorld());
		ABaseCharacter*Player = Cast<ABaseCharacter>(PC->GetPawn());
		UCharacterMovementComponent*MovementComp = Player->GetCharacterMovement();
		if (GetWalkSpeed() <= 500.0f)  // 速度上限500
		{
			// GE修改WalkSpeed这个属性之后会立马执行这里，直接获取到移动组件去设置速度，不再蓝图里添加广播事件了
			if (Player)
			{
				MovementComp->MaxWalkSpeed = GetWalkSpeed();
			}
		}
		else
		{
			MovementComp->MaxWalkSpeed = 500.0f;
		}
	}
}




