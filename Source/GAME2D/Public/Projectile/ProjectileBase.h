// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAME2D/Public/Character/BaseCharacter.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class UPaperFlipbookComponent;

UENUM(BlueprintType)
enum class EMyActorState : uint8
{
	Active     UMETA(DisplayName = "Active"),
	Recycle      UMETA(DisplayName = "Recycle")
};


UCLASS()
class GAME2D_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* FilpBookComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EMyActorState CurrentState;
	
	FTimerHandle TimerHandle;

	TWeakObjectPtr<ABaseCharacter> TargetSelf; // 发射该物体的Character

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:	
    UFUNCTION(BlueprintCallable)
	void InitSelf(UPaperFlipbook *Flipbook,FVector Speed,float Cycle); // 初始化
	UFUNCTION(BlueprintCallable)
	void SetRotate(); // 生成之后设置相对该Character的旋转
	UFUNCTION(BlueprintCallable)
	void Recycle(); // 回收
};
