// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HeroYue.h"
#include "GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#include"Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Weapon/WeaponGun.h"
#include "DrawDebugHelpers.h"
#include "InteractActor/InteractActorBase.h"
#include "Universal/InteractInterface.h"
#include "Component/HealthComponent.h"

// Sets default values
AHeroYue::AHeroYue()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it
	PrimaryActorTick.bCanEverTick = true;
	
	//摄像机组件和弹簧臂组件的创建与设置
	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm"));
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	MySpringArm->SetupAttachment(GetCapsuleComponent());
	MyCamera->SetupAttachment(MySpringArm);
	MySpringArm->SetRelativeRotation(FRotator(-20.0f, -13.0f, 0.0f));
	MySpringArm->TargetArmLength = 300.0f;
	MyCamera->SetRelativeLocation(FVector::ZeroVector);
	MySpringArm->SocketOffset = FVector(0.0f, 65.0f, 30.0f);
	MySpringArm->bUsePawnControlRotation= true;
	MySpringArm->bEnableCameraLag = true;
	MyCamera->bUsePawnControlRotation = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	JumpMaxHoldTime = 0.2f;
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.3f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	bIsInteract = false;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
//激活输入映射上下文
void AHeroYue::BeginPlay()
{
	Super::BeginPlay();
	//获取玩家控制器
	if (APlayerController* MyPlayerController = Cast<APlayerController>(GetController()))
	{
		//获取输入子系统
		FRotator InitialRotation = MyPlayerController->GetControlRotation();
		InitialRotation.Pitch = -20.0f;
		Controller -> SetControlRotation(InitialRotation);

		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MyPlayerController->GetLocalPlayer()))
		{
			//添加输入映射上下文
			InputSystem->AddMappingContext(HeroIMC, 0);
		}
		if (MySpringArm)
		{	
			DefaultArmLength = MySpringArm->TargetArmLength;
		}
	}
	
	//生成武器实例
	if (WeaponClass && !CurrentWeapon)
	{
		//定义归属
		FActorSpawnParameters SpawnParms;
		SpawnParms.Owner = this;
		SpawnParms.Instigator = this;
		//生成位置
		FVector SpawnLocation = GetMesh()->GetSocketLocation(FName("WeaponSocket"));
		FRotator SpawnRotation = GetMesh()->GetSocketRotation(FName("WeaponSocket"));
		//生成
		CurrentWeapon = GetWorld()->SpawnActor<AWeaponGun>(
			WeaponClass,
			SpawnLocation,
			SpawnRotation,
			SpawnParms
		);
		
		
		
	}
	//将武器附加到角色
	if (CurrentWeapon)
	{
		//定义粘贴规则
		FAttachmentTransformRules AttachRules(
			EAttachmentRule::SnapToTarget,//位置，插槽
			EAttachmentRule::SnapToTarget,//旋转，插槽
			EAttachmentRule::KeepWorld,//缩放，保持原样
			false      //不模拟物理
		);
		//粘贴到插槽
		CurrentWeapon->AttachToComponent(
			GetMesh(),
			AttachRules,
			FName("WeaponSocket")
		
		);
		
		
	}
}

// Called every frame
void AHeroYue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
		Firetime+=DeltaTime;
		if (Firetime>=0.2f)
		{
			Firetime = 0.0f;
			bCanFire = true;
		}
		else
		{
			bCanFire = false;
		}

	
	if (bIsInteract)
	{
		InteractionTime += DeltaTime;
		if (InteractionTime>=0.1f)
		{
			//GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Cyan,TEXT("尝试交互") );
			Interact();
			InteractionTime = 0.0f;
		}
	}

	if (MySpringArm)
	{
		float TargetLength = bIsAiming ? AimArmLength : DefaultArmLength;
		float NewLength = FMath::FInterpTo(MySpringArm->TargetArmLength,TargetLength,DeltaTime,FireInterpSpeed);
		MySpringArm->TargetArmLength = NewLength;
	}
	
}

// Called to bind functionality to input
//绑定输入功能
void AHeroYue::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//转换为增强输入组件
	if (UEnhancedInputComponent* EI = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EI->BindAction(HeroMove,ETriggerEvent::Triggered,this,&AHeroYue::Move);
		EI->BindAction(HeroLook,ETriggerEvent::Triggered,this,&AHeroYue::Look);
		EI->BindAction(HeroJump,ETriggerEvent::Started,this,&AHeroYue::Jump);
		EI->BindAction(HeroJump,ETriggerEvent::Completed,this,&AHeroYue::StopJumping);
		EI->BindAction(HeroShot,ETriggerEvent::Started,this,&AHeroYue::StartFire);
		EI->BindAction(HeroShot,ETriggerEvent::Triggered,this,&AHeroYue::OnFire);
		EI->BindAction(HeroShot,ETriggerEvent::Completed,this,&AHeroYue::StopFire);
	}
	PlayerInputComponent->BindKey(EKeys::E,IE_Pressed,this,&AHeroYue::DoInteract);
	PlayerInputComponent->BindKey(EKeys::Q,IE_Pressed,this,&AHeroYue::HealthCast);

}

//移动函数
void AHeroYue::Move(const FInputActionValue& Value)
{
	FVector2D Movement = Value.Get<FVector2D>();
	//获取正方向
	if (Controller != nullptr)
	{
		FRotator Rot = Controller->GetControlRotation();
		FRotator YawRot(0.0f, Rot.Yaw, 0);
		//前方向量
		FVector forwardDirection = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		//右方向量
		FVector rightDirection = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

		AddMovementInput(forwardDirection,Movement.Y);
		AddMovementInput(rightDirection,Movement.X);
	}
}

//视角函数
void AHeroYue::Look(const FInputActionValue& Value)
{
 	FVector2D Movement = Value.Get<FVector2D>();
 	if (Controller != nullptr)
 	{
 		// 直接处理视角输入，使摄像机与控制器同步
 		AddControllerPitchInput(Movement.Y);
 		AddControllerYawInput(Movement.X);
 	}
}

void AHeroYue::StartFire(const FInputActionValue& Value)
{
	//进入瞄准状态
	bIsAiming = true;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	//播放瞄准动画
	if (MontageFire)
	{
		PlayAnimMontage(MontageFire, 1.0f);
	}
	
}

void AHeroYue::OnFire(const FInputActionValue& Value)
{
	if (bCanFire)
	{
		FHitResult OutHit;
		DoLineTrace(OutHit,10000.0f);
		if (CurrentWeapon)
		{
			CurrentWeapon->Fire(OutHit.Location);
		}
	}
}

void AHeroYue::StopFire(const FInputActionValue& Value)
{
	//退出瞄准状态
	bIsAiming = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//退出瞄准动画
	if (GetMesh()->GetAnimInstance())
	{
		GetMesh()->GetAnimInstance()->Montage_Stop(0.2f,MontageFire);
	}
}

void AHeroYue::Interact()
{
	FHitResult OutHit;
	DoLineTrace(OutHit,460.0f);
	TargetInteractActor = OutHit.GetActor();

}

void AHeroYue::HealthCast()
{
	HealthComponent->ApplyHealthChange(-10.0f,this);
}

void AHeroYue::DoInteract()
{
	if (bIsInteract == true)
	{
		if (AInteractActorBase* InteractActor = Cast<AInteractActorBase>(TargetInteractActor))
		{
			IInteractInterface::Execute_Interact(InteractActor,this);
		}
	}
}


bool AHeroYue::DoLineTrace(FHitResult& OutHit, float TraceDistance)
{
	//获取起点位置和方向
	FVector StartLocation;
	FRotator StartRotation;
	Controller->GetPlayerViewPoint(StartLocation,StartRotation);
	
	//获取终点位置
	FVector EndLocation = StartLocation + (StartRotation.Vector() * TraceDistance);
	//设置参数过滤并发射
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);//忽略自己
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		OutHit,	
		StartLocation,
		EndLocation,
		ECC_Visibility,
		CollisionParams
	);
	//绘制调试线
	if (bHit)
	{
		DrawDebugLine(GetWorld(),StartLocation,OutHit.Location,FColor::Green,false,1.0f);
		DrawDebugSphere(GetWorld(),OutHit.Location,5.0f,12,FColor::Yellow,false,1.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(),StartLocation,EndLocation,FColor::Red,false,1.0f);
		OutHit.Location = StartLocation + (StartRotation.Vector() * TraceDistance);
	}
	return bHit;
}

