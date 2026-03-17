// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseEnemy.h"
#include "PaperFlipbookComponent.h"
#include "GAME2D/Public/Projectile/ProjectileBase.h"
#include "GameFramework/Actor.h"
#include "BaseObjectManager.generated.h"
/*
 * 对象池管理器
 * 目前管理：玩家剑气生成物
 */

UCLASS()
class GAME2D_API ABaseObjectManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseObjectManager();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ObjectPool")
	TArray<AProjectileBase*>ProjectPool; // 飞行物对象池
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectPool")
	TSubclassOf<AProjectileBase> ProjectileBlueprintClass; 

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ObjectPool")
	TArray<ABaseEnemy*>EnemyProjectPool; // 敌人对象池
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectPool")
	TSubclassOf<ABaseEnemy> EnemyClass; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// 设置飞行物的对象池
	UFUNCTION(BlueprintCallable,Category="ObjectPool")
	void SetObjectPool(FVector Start,FVector Speed,UPaperFlipbook *Filpbook,float Cycle); 

	// 设置敌人对象池
	UFUNCTION(BlueprintCallable,Category="ObjectPool")
	void SetEnemyObjectPool(FVector SpawnLoaction);
	
};
