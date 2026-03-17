// Fill out your copyright notice in the Description page of Project Settings.



#include "GAME2D/Public/Gameplay/MyPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Character/BaseCharacter.h"
#include "Engine/LocalPlayer.h"
#include "GAS/BaseAttributeSet.h"



void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem*Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext,0);
	}
}

