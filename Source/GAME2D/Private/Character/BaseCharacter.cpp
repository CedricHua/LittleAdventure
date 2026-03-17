// Fill out your copyright notice in the Description page of Project Settings.



#include "GAME2D/Public/Character/BaseCharacter.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "AbilitySystemComponent.h"
#include "BackpackSystem/BackpackComponent.h"
#include "GAME2D/Public/GAS/BaseAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/MyBlueprintFunctionLibrary.h"
#include "Gameplay/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"


ABaseCharacter::ABaseCharacter()
{
	// 绑定组件
	MyASC = CreateDefaultSubobject<UBaseAbilitySystemComponent>("MyASC");
	TaskSystemComp = CreateDefaultSubobject<UTaskSystemComp>("TaskSystemComp");
	BackpackComponent = CreateDefaultSubobject<UBackpackComponent>(TEXT("BackPackComp"));
	Dir_Y = -1.0f;

	// 监听GAS属性变化（变化时广播）
	MyASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetHPAttribute()).AddUObject(this,&ABaseCharacter::OnHPAttributeChanged);
	MyASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetMPAttribute()).AddUObject(this,&ABaseCharacter::OnMPAttributeChanged);
	MyASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetStrengthAttribute()).AddUObject(this,&ABaseCharacter::OnStrengthAttributeChanged);
	MyASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetArmorAttribute()).AddUObject(this,&ABaseCharacter::OnArmorAttributeChanged);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetVel(); // 记录变量（仅用于计算生成物的旋转角）
}

// BindEnhancedInput
void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	
	if (UEnhancedInputComponent*EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);
	}
	
}

// 移动
void ABaseCharacter::Move(const FInputActionValue& Value)
{
	// 用于获取朝向，设置球形检测的位置
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// 根据输入更新角色的旋转
		if (MovementVector.X > 0.0f) // D
		{
			Dir_X = 25.0f;
			Dir_Y = 0.0f; 
		}
		else if (MovementVector.X < 0.0f) // A
		{
			Dir_X = -25.0f;
			Dir_Y = 0.0f; 
		}
		else if (MovementVector.Y > 0.0f) // W
		{
			Dir_X = 0.0f;
			Dir_Y = -25.0f;
		}
		else if (MovementVector.Y < 0.0f) // S
		{
			Dir_X = 0.0f;
			Dir_Y = 25.0f;
		}

		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

// GAS
// 属性变化时发送广播，更新值
void ABaseCharacter::OnHPAttributeChanged(const FOnAttributeChangeData& Data)
{
	HPChangeEvent.Broadcast(Data.NewValue);
}
void ABaseCharacter::OnMPAttributeChanged(const FOnAttributeChangeData& Data)
{
	MPChangeEvent.Broadcast(Data.NewValue);
}
void ABaseCharacter::OnStrengthAttributeChanged(const FOnAttributeChangeData& Data)
{
	StrengthChangeEvent.Broadcast(Data.NewValue);
}

void ABaseCharacter::OnArmorAttributeChanged(const FOnAttributeChangeData& Data)
{
	ArmorChangeEvent.Broadcast(Data.NewValue);
}

void ABaseCharacter::ActivateTag(UAbilitySystemComponent* ASC, FGameplayTag Tag)
{
	if (!ASC || !Tag.IsValid())
	{
		return;
	}

	ASC->AddLooseGameplayTag(Tag);
}

void ABaseCharacter::DeactivateTag(UAbilitySystemComponent* ASC, FGameplayTag Tag)
{
	if (!ASC || !Tag.IsValid())
	{
		return;
	}
	ASC->RemoveLooseGameplayTag(Tag);
}


// ***********工具函数************
// 处理碰撞检测以及结果（不改）
ACharacter* ABaseCharacter::SpawnAndHit(float X, float Y)
{
	
	//GEngine->AddOnScreenDebugMessage(1,5.0f,FColor::Red,FString::Printf(TEXT("Dir_X:%f,Dir_Y:%f"),X,Y));
	APlayerController* PlayerController= GetWorld()->GetFirstPlayerController();
	if (!PlayerController || GetWorld() == nullptr)
	{
		return nullptr;
	}
	
	FVector PlayerLocation = GetActorLocation();
	
	FVector Start = PlayerLocation + FVector(X, Y, 0.0f);  
	FVector End   = PlayerLocation + FVector(X, Y, 0.0f);
	
	float SphereRadius = 15.0f;
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	TArray<FHitResult> HitResults;
	TArray<AActor*> ActorsToIgnore;
	
	bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),
		Start,
		End,
		SphereRadius, 
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResults,
		true,FLinearColor::Red,FLinearColor::Green,5
	);
	
	ACharacter* FirstHitCharacter = nullptr;
	for (const FHitResult& Hit : HitResults)
	{
		if (ACharacter* Char = Cast<ACharacter>(Hit.GetActor()))
		{
			FirstHitCharacter = Char;
			break;
		}
	}
	return FirstHitCharacter;
}



// 记录速度方向（不改）
void ABaseCharacter::SetVel()
{
	if (UCharacterMovementComponent * MovementComp = GetCharacterMovement())
	{
		if (MovementComp->Velocity.GetSafeNormal(0.0001f).X != 0.0f && MovementComp->Velocity.GetSafeNormal(0.0001f).Y != 0.0f)
		{
			if (Vel_X !=MovementComp->Velocity.GetSafeNormal(0.0001f).X  &&  Vel_Y != MovementComp->Velocity.GetSafeNormal(0.0001f).Y )
			{
				Vel_X = MovementComp->Velocity.GetSafeNormal(0.0001f).X;
				Vel_Y = MovementComp->Velocity.GetSafeNormal(0.0001f).Y;
			}
		}
	}
}
// 计算生成物旋转角（不改）
float ABaseCharacter::GetAngle()
{
	float Yaw_Angle =(180.0)/UE_DOUBLE_PI * FMath::Atan2(Vel_Y,Vel_X);
	if (Yaw_Angle < 0.0f)
	{
		Yaw_Angle += 360.0f;
		return Yaw_Angle;
	}
	return Yaw_Angle;
}

void ABaseCharacter::GetExperience(float inExperience, TSubclassOf<UGameplayEffect> LevelUpEffectClass)
{
	// 每次获取经验的时候设置玩家等级
	UMyGameInstance* MyGameInstance = UMyBlueprintFunctionLibrary::GetGameInstanceBase(this);
	float C_XP = MyGameInstance->PlayerXP += inExperience;

	UHUD_All_UI* HUD_All_UI = UMyBlueprintFunctionLibrary::GetHUDAllUI(this);
	HUD_All_UI->UMG_Main->Bar_Experience->SetPercent(FMath::Fmod(C_XP, 100.0f) / 100);

	int32 NewLevel = FMath::FloorToInt(C_XP / 100.0f);
	GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, FString::Printf(TEXT("NewLevel:%d  PlayerLevel:%d"), NewLevel,MyGameInstance->PlayerLevel));
	if (NewLevel > MyGameInstance->PlayerLevel)  // 检测到玩家等级发生变化
	{
		// 设置玩家等级
		MyGameInstance->PlayerLevel = FMath::FloorToInt(C_XP / 100.0f);
		// 设置玩家属性
		UBaseAbilitySystemComponent*ASC=this->MyASC;
		if (ASC && LevelUpEffectClass)
		{
			// 创建Effect Context
			FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
			ContextHandle.AddSourceObject(this);
			GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Blue, FString::Printf(TEXT("NewLevel:%d  PlayerLevel:%d"), NewLevel,MyGameInstance->PlayerLevel));
			// 应用GE
			ASC->ApplyGameplayEffectToSelf(
				LevelUpEffectClass.GetDefaultObject(),  // 获取GE的默认对象
				static_cast<float>(MyGameInstance->PlayerLevel),  // 将PlayerLevel转为float
				ContextHandle                            // 上下文
			);
			GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Blue, FString::Printf(TEXT("应用GE，应用时：PlayerLevel:%d"), MyGameInstance->PlayerLevel));
		}
	}
}
