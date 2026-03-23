// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/BaseUseItemAbility.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Gameplay/MyGameInstance.h"


void UBaseUseItemAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    if (!CurrentActorInfo || !CurrentActorInfo->AbilitySystemComponent.IsValid())
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }
    UMyGameInstance*GameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
    UAbilitySystemComponent* ASC = CurrentActorInfo->AbilitySystemComponent.Get();
    
    // 1. 获取当前AbilitySpec
    FGameplayAbilitySpec* AbilitySpec = ASC->FindAbilitySpecFromHandle(Handle);
    if (!AbilitySpec)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }
    
    // 2. 从DynamicAbilityTags中查找物品标签
    FGameplayTag FoundItemTag = FGameplayTag::EmptyTag;
    
    for (const FGameplayTag& Tag : AbilitySpec->DynamicAbilityTags)
    {
        // 查找以"Item."开头的标签
        if (Tag.ToString().StartsWith("Item."))
        {
            FoundItemTag = Tag;
            break;
        }
    }
    
    // 3. 如果找到物品标签，查找对应的GE
    if (FoundItemTag.IsValid())
    {
        TSubclassOf<UGameplayEffect>* EffectClassPtr = ItemEffectMap.Find(FoundItemTag);
        if (EffectClassPtr && *EffectClassPtr)
        {
            // 4. 应用对应的GameplayEffect
            FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
            EffectContext.AddSourceObject(this);
            
            FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(
                *EffectClassPtr, 
                GameInstance->PlayerLevel, 
                EffectContext
            );
            
            if (SpecHandle.IsValid())
            {
                ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
                //GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, TEXT("GE激活"));
                
            }
        }
    }
    
    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
