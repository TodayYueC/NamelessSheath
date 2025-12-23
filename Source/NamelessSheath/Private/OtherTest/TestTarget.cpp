// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherTest/TestTarget.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "NiagaraFunctionLibrary.h"
//#include "NiagaraSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Component/HealthComponent.h"

// Sets default values
ATestTarget::ATestTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMesh"));
	RootComponent = TargetMesh;
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	
}

// Called when the game starts or when spawned
void ATestTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

float ATestTarget::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (ActualDamage > 0.0f)
	{
		HealthComponent->ApplyHealthChange(-ActualDamage, DamageCauser);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("受到伤害!，当前剩余血量:") + FString::SanitizeFloat(HealthComponent->GetCurrentHealth()));
	}
	if (HealthComponent->GetCurrentHealth() <= 0.0f)
	{	
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("血条清空，对象死亡!"));
		if (ExplosionVFX)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				this,
				ExplosionVFX,
				GetActorLocation(),
				GetActorRotation()
			);
		}
		if (ExplosionSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				ExplosionSound,
				GetActorLocation()
			);
		}
		Destroy();
	}
	return ActualDamage;
}

// Called every frame
void ATestTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

