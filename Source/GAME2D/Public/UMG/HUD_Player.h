// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAME2D/Public/UMG/HUD_All_UI.h"
#include "GameFramework/HUD.h"
#include "HUD_Player.generated.h"

/**
 * 
 */
UCLASS()
class GAME2D_API AHUD_Player : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="HUD")
	UHUD_All_UI* HUD_All_UI;
	
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void UpdateUI();
	void Callback_Function(){};
	
};
