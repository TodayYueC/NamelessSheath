// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Bullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//初始化组件
	//碰撞体
	BulletCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BulletCollision"));
	RootComponent = BulletCollision;
	BulletCollision->InitSphereRadius(5.0f);
	BulletCollision->SetCollisionProfileName(TEXT("Ragdoll"));
	BulletCollision->SetNotifyRigidBodyCollision(true);
	//模型
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(BulletCollision);
	BulletMesh->SetCollisionProfileName(TEXT("NoCollision"));
	//发射物移动组件
	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));
	BulletMovement->UpdatedComponent = BulletCollision;
	BulletMovement->InitialSpeed = 8000.0f;
	BulletMovement->MaxSpeed = 8000.0f;
	BulletMovement->ProjectileGravityScale = 0.0f;
	BulletMovement->bRotationFollowsVelocity = true;
	BulletMovement->bShouldBounce = true;
	
	//初始化生命周期
	InitialLifeSpan = 3.0f;
	
	//BulletCollision->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	BulletCollision->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Bullet Hit!"));
	if (OtherActor != this && OtherComp && OtherActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Bullet Hit!"));
		
		UGameplayStatics::ApplyDamage(
			OtherActor,
			20.0f,
			GetInstigatorController(),
			this,
			UDamageType::StaticClass()
			);
		
		
		//销毁子弹
		Destroy();
	}
}

