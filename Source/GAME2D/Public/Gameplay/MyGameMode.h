// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBlueprintFunctionLibrary.h"
#include "GameFramework/GameModeBase.h"
#include "UMG/BlueprintUIInterface.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAME2D_API AMyGameMode : public AGameModeBase , public IBlueprintUIInterface
{
	GENERATED_BODY()
public:

	UPROPERTY()
	APlayerController* PC = nullptr;
	
	UPROPERTY()
	UUserWidget* MyWidgetInstance = nullptr;  // 需要实例的UI
	
	virtual void BeginPlay() override;
	
	void SetPlayerSpawnPoint();
	void CreateBeginUI();

	UFUNCTION(BlueprintImplementableEvent,Category="SaveGame")
	void AutoSaveGame();
};
