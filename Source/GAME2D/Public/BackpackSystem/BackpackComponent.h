// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Manager/StructManager.h"
#include "UMG/BlueprintUIInterface.h"
#include "BackpackComponent.generated.h"

class AItemBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME2D_API UBackpackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBackpackComponent();

	UFUNCTION(BlueprintCallable,Category="BackpackSystem")
	void AddItem(FItem_Struct NewItem,AItemBase* ItemRef);

	UFUNCTION(BlueprintCallable,Category="BackpackSystem")
	void ReduceItem(int32 SlotIndex);

	UPROPERTY()
	UUserWidget* WidgetToNotify = nullptr;  // 需要实例的UI
};
