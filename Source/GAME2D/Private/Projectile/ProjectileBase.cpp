// Fill out your copyright notice in the Description page of Project Settings.




#include "Projectile/ProjectileBase.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "GAME2D/Public/Character/BaseCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FilpBookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FilpBook"));
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f; // 设置重力为0
	ProjectileMovementComponent->Velocity = FVector(0.0f, 0.0f, 0.0f); // 设置速度为0
	ProjectileMovementComponent->Friction=0.0f; // 设置磨擦力为0
}


void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	ABaseCharacter* Player = Cast<ABaseCharacter>(PC->GetPawn()) ;
	TargetSelf = Player;  // 由玩家发射，生成目标设置成玩家
	
}

// 初始化（为玩家释放技能时调用）
void AProjectileBase::InitSelf(UPaperFlipbook *Flipbook, FVector Speed, float Cycle)
{
	FilpBookComponent->SetFlipbook(Flipbook); 
	ProjectileMovementComponent->Velocity = Speed;  // 初始化速度
	CurrentState = EMyActorState::Active;  // 设置对象池属性为已激活

	// 设置定时器，定时回收
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&AProjectileBase::Recycle,Cycle,false,1.0f);
	}
}

// 设置自身旋转方向
void AProjectileBase::SetRotate()
{
	float Angle = TargetSelf->GetAngle();
	this->SetActorRotation(FRotator(0.0f,Angle,90.0f));

}

// 回收到对象池中
void AProjectileBase::Recycle()
{
	FilpBookComponent->SetFlipbook(nullptr);
	SetActorLocation(FVector(0.0,0.0,-200.0),false,nullptr);
	CurrentState = EMyActorState::Recycle;
}




