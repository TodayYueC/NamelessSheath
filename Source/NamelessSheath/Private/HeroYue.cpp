// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroYue.h"
#include "GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#include"Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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
	MyCamera->SetRelativeLocation(FVector(0.0f, 65.0f, 0.0f));
	MySpringArm->bUsePawnControlRotation= true;
	MyCamera->bUsePawnControlRotation = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	JumpMaxHoldTime = 0.2f;
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.3f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
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
	}
}

// Called every frame
void AHeroYue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	}

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
		AddControllerPitchInput(Movement.Y);
		AddControllerYawInput(Movement.X);
	}
}

