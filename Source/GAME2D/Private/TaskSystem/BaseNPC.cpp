// Fill out your copyright notice in the Description page of Project Settings.


#include "GAME2D/Public/TaskSystem/BaseNPC.h"


ABaseNPC::ABaseNPC()
{
	TaskSystemComp = CreateDefaultSubobject<UTaskSystemComp>("TaskSystemComp");
}

void ABaseNPC::SetNPC()
{
	if (!TaskSystemComp) return;
	TaskSystemComp->HitNPC = this;
}
