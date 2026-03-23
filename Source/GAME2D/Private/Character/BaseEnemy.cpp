// Fill out your copyright notice in the Description page of Project Settings.



#include "GAME2D/Public/Character/BaseEnemy.h"

void ABaseEnemy::InitSelf()
{
	CurrentState = EActorState::Active;  // 初始化设置自身状态为已激活
	
}

// 回收
void ABaseEnemy::RecycleSelf()
{
	SetActorLocation(FVector(0.0,0.0,-200.0),false,nullptr);
	CurrentState = EActorState::Recycle;
}

void ABaseEnemy::SetCurrentDir(float X, float Y)
{
	// 在父类的tick中实时更新
	X = this->Vel_X;  
	Y = this->Vel_Y;
	if ((X >= 0.7f && X <= 1.0f) &&  (Y >= -0.7f &&  Y <= 0.7f))
	{
		E_Dir_X = 25.0,E_Dir_Y = 0.0; // 右

	}
	else if ( (X >= -1.0f && X <= -0.7f) && (Y >= -0.7f &&  Y <= 0.7f))
	{
		E_Dir_X = -25.0,E_Dir_Y = 0.0; // 左

	}
	else if ((X >= -0.7f && X <= 0.7f) && (Y >= 0.7f && Y <= 1.0f))
	{
		E_Dir_X = 0.0,E_Dir_Y = 25.0; // 下

	}
	else if ((X >= -0.7f && X <= 0.7f) && (Y >= -1.0f && Y <= -0.7f))
	{
		E_Dir_X = 0.0,E_Dir_Y = -25.0; // 上
	}
}

ACharacter* ABaseEnemy::E_SpawnAndHit(float X, float Y)
{
	SetCurrentDir(0,0);
	// GEngine->AddOnScreenDebugMessage(1,5.0f,FColor::Yellow,FString::Printf(TEXT("Dir_X:%f,Dir_Y:%f"),E_Dir_X ,E_Dir_Y));
	return SpawnAndHit(E_Dir_X,E_Dir_Y);
}
