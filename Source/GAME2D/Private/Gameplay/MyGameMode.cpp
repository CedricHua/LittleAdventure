// Fill out your copyright notice in the Description page of Project Settings.


#include "GAME2D/Public/Gameplay/MyGameMode.h"
#include "Gameplay/MyBlueprintFunctionLibrary.h"
#include "Gameplay/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// 获取PlayerController
	this->PC = UMyBlueprintFunctionLibrary::GetPlayerController(this);
	UMyGameInstance* GameInstance = UMyBlueprintFunctionLibrary::GetGameInstanceBase(this);
	if (!PC) return;
	
	
	// 初始设置玩家出生点
	SetPlayerSpawnPoint();
	
	// 临时禁用玩家移动
	UMyBlueprintFunctionLibrary::PlayerMoveController(false, this);
	

	// 显示指针（测试用）
	PC->SetShowMouseCursor(true);
	
	// 创建关卡初始UI
	CreateBeginUI();

	// 游戏开始时响应一次CallEvent
	if (GameInstance->bShouldCallEvent)
	{
		if (PC && PC->GetPawn())
		{
			ABaseCharacter* Player = Cast<ABaseCharacter>(PC->GetPawn());
			if (Player && Player->TaskSystemComp)
			{
				// 使用弱引用捕获，避免悬垂指针
				TWeakObjectPtr<UTaskSystemComp> WeakTaskComp = Player->TaskSystemComp;
			
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(
					TimerHandle,
					[WeakTaskComp]() 
					{
						// 只检查弱引用是否有效
						if (WeakTaskComp.IsValid())
						{
							WeakTaskComp->CallEvent();
						}
					},
					2.0f,
					false
				);
			}
		}
	}
	

	// 重新启用玩家移动
	UMyBlueprintFunctionLibrary::PlayerMoveController(true, this);
}

void AMyGameMode::SetPlayerSpawnPoint()
{
	// 获取必要的对象
	UMyGameInstance* GameInstance = UMyBlueprintFunctionLibrary::GetGameInstanceBase(this);
	if (!GameInstance) return;
	
	if (!PC) return;
	ABaseCharacter* Player = Cast<ABaseCharacter>(PC->GetPawn());
	if (!Player) return;

	// 根据任务索引设置出生点
	switch (GameInstance->MissionIndex)
	{
	case 0:
		Player->SetActorLocation(FVector(-2034.0f, -6.0f, 12.0f));
		break;
	case 1:
		Player->SetActorLocation(FVector(0.0f, 500.0f, 12.0f));
		break;
	case 2:
		Player->SetActorLocation(FVector(180.0f, -1480.0f, 15.0f));
		break;
	case 4:
		Player->SetActorLocation(FVector(-1650.0f, 760.0f, 12.0f));
		break;
	case 5:
		
		Player->SetActorLocation(FVector(1170.0f, -1480.0f, 15.0f));
		break;
	}
}  

void AMyGameMode::CreateBeginUI()
{
	if (!PC) return;
	
	// 创建UI
	TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/UMG/EnterAndExitMap.EnterAndExitMap_C"));
	if (!WidgetClass) return;
	
	MyWidgetInstance = CreateWidget(PC, WidgetClass);
	if (MyWidgetInstance)
	{
		MyWidgetInstance->AddToViewport();
		// 通过接口调用函数
		Execute_PlayUIAnimation(MyWidgetInstance, true);
	}
}
// void AMyGameMode::BeginPlay()
// {
// 	Super::BeginPlay();
// 	UMyGameInstance* MyGameInstance = UMyBlueprintFunctionLibrary::GetGameInstanceBase(this);
// 	// 记录当前地图的名字，存储在Gameinstance里
// 	if (MyGameInstance)
// 	{
// 		// 记录当前地图的名字，存储在Gameinstance里
// 		MyGameInstance->CurrentMapName = UGameplayStatics::GetCurrentLevelName(this, true);	
// 	}
// 	
// 	this->PC = UMyBlueprintFunctionLibrary::GetPlayerController(this);
// 	if (!PC)
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerController in AMyGameMode::BeginPlay()"));
// 		return;
// 	}
// 	// 地图加载的初始化
// 	// 1.初始设置玩家出生点
// 	SetPlayerSpawnPoint();
// 	UMyBlueprintFunctionLibrary::PlayerMoveController(false,this);  // !!!
//
// 	// 2.显示指针（正式手游没有，电脑测试用，之后要去掉）
// 	PC->SetShowMouseCursor(true);
// 	
// 	// 3.创建关卡初始UI，并加载动画
// 	CreateBeginUI();
//
// 	// 响应一次CallEvent
// 	ABaseCharacter* Player = Cast<ABaseCharacter>(this->PC->GetPawn());
// 	FTimerHandle TimerHandle;
// 	GetWorld()->GetTimerManager().SetTimer(
// 		TimerHandle,
// 		[Player]() 
// 		{
// 			Player->TaskSystemComp->CallEvent();
// 		},
// 		2.0f,  // 延迟
// 		false  // 不循环
// 	);
// 	UMyBlueprintFunctionLibrary::PlayerMoveController(true,this);
// }
//
// void AMyGameMode::SetPlayerSpawnPoint()
// {
// 	/*  地图切换时设置玩家的出生点  */
// 	UMyGameInstance* GameInstance = UMyBlueprintFunctionLibrary::GetGameInstanceBase(this);
// 	if (!GameInstance) return;
// 	ABaseCharacter* Player = Cast<ABaseCharacter>(this->PC->GetPawn());
// 	if (!Player) return;
// 	switch (GameInstance->MissionIndex)
// 	{
// 	case 0:
// 		Player->SetActorLocation(FVector(-2034.0f, -6.0f, 12.0f), false, nullptr, ETeleportType::None);
// 		break;
// 	case 1:
// 		Player->SetActorLocation(FVector(0.0f, 500.0f, 12.0f), false, nullptr, ETeleportType::None);
// 		break;
// 	case 2:
// 		Player->SetActorLocation(FVector(180.0f, -1480.0f, 12.0f), false, nullptr, ETeleportType::None);
// 		break;
// 	case 4:
// 		Player->SetActorLocation(FVector(-1650.0f, 760.0f, 12.0f), false, nullptr, ETeleportType::None);
// 		break;
// 	case 5:
// 		Player->SetActorLocation(FVector(1170.0f, -1480.0f, 12.0f), false, nullptr, ETeleportType::None);
// 		break;
// 	}
// }  
//
// void AMyGameMode::CreateBeginUI()
// {
// 	/*  创建UI然后通过接口调用其中的函数  */
// 	TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUserWidget>(nullptr,TEXT("/Game/UMG/EnterAndExitMap.EnterAndExitMap_C"));
// 	MyWidgetInstance = CreateWidget(PC,WidgetClass);
// 	MyWidgetInstance -> AddToViewport();
// 	// 通过接口调用函数
// 	Execute_PlayUIAnimation(MyWidgetInstance, true);
// }


	
