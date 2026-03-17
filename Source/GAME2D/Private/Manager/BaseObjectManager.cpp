// Fill out your copyright notice in the Description page of Project Settings.

#include "GAME2D/Public/Manager/BaseObjectManager.h"

#include "GAME2D/Public/Projectile/ProjectileBase.h"
#include "Gameplay/MyBlueprintFunctionLibrary.h"
#include "Gameplay/MyGameInstance.h"


ABaseObjectManager::ABaseObjectManager()
{
}

// Called when the game starts or when spawned
void ABaseObjectManager::BeginPlay()
{
	Super::BeginPlay();
}


// 生成发射物对象（已完善，不用修改）
void ABaseObjectManager::SetObjectPool(FVector Start, FVector Speed, UPaperFlipbook* Filpbook, float Cycle)
{
	AProjectileBase* BaseObject = nullptr;
	for (AProjectileBase* Object : ProjectPool)
	{
		if (Object->CurrentState == EMyActorState::Recycle)
		{
			BaseObject = Object;
			break;
		}
	}
	if (!BaseObject)
	{
		UWorld* World = GetWorld();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = BaseObject;
	
		if (World && ProjectileBlueprintClass) 
		{
			if (AProjectileBase* SpawndActor = World->SpawnActor<AProjectileBase>(ProjectileBlueprintClass, Start, FRotator(0.0f, 0.0f, 0.0f), SpawnParams))
			{
				BaseObject = SpawndActor;
				ProjectPool.Add(BaseObject);
				BaseObject->InitSelf(Filpbook, Speed, Cycle);
			}
		}
	}
	else
	{
		BaseObject->InitSelf(Filpbook, Speed, Cycle);
	}
	if (BaseObject)
	{
		BaseObject->SetActorLocation(Start); // 生成该物体的Character位置
		BaseObject->SetRotate();
	}
}

void ABaseObjectManager::SetEnemyObjectPool(FVector SpawnLoaction)
{
	ABaseEnemy* BaseObject = nullptr;
	for (ABaseEnemy* Object : EnemyProjectPool)
	{
		if (IsValid(Object) && Object->CurrentState == EActorState::Recycle)  // !!
		{
			BaseObject = Object;
			break;
		}
	}
	if (!BaseObject)
	{
		// 处于回收状态（无效），创建出来
		UWorld* World = GetWorld();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = BaseObject;

		if (World && EnemyClass) 
		{
			if (ABaseEnemy* SpawndActor = World->SpawnActor<ABaseEnemy>(EnemyClass, FVector(0.0f,0.0f,-1000.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams))
			{
				BaseObject = SpawndActor;
				EnemyProjectPool.Add(BaseObject);
				BaseObject->InitSelf();
			}
		}
	}
	else
	{
		// 有效，直接初始化
		BaseObject->InitSelf();
	}
	if (BaseObject)
	{
		BaseObject->SetActorLocation(SpawnLoaction);  // 哪个生成器调用，就生成在哪里
	}
}



