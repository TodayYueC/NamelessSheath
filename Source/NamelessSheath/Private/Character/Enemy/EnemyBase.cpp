// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/EnemyBase.h"
#include "Component/HealthComponent.h"
#include "Components/SphereComponent.h"
#include "System/EnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	RangeToChase = CreateDefaultSubobject<USphereComponent>("RangeToChase");
	RangeToChase->SetupAttachment(RootComponent);
	
	//AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bUseControllerRotationYaw = false;
	// 2. 开启“朝向移动方向”
	// 只有开了这个，角色才会根据 MoveTo 的路径自动转身
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 3. 设置转身速度 (RotationRate)
	// 这里的 Yaw (Z轴) 决定了转身快慢
	// 360 = 慢悠悠，720 = 敏捷，2000 = 瞬间
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

