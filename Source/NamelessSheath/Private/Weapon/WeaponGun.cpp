// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponGun.h"
#include "Weapon/Bullet.h"

// Sets default values
AWeaponGun::AWeaponGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	RootComponent = GunMesh;
	
	GunMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AWeaponGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponGun::Fire()
{
	if (BulletClass && GunMesh)
	{
		const FName BulletSocketName("BulletSpawnLocation");
		FVector SpawnLocation = GunMesh->GetSocketLocation(BulletSocketName);
		FRotator SpawnRotation = GetActorRotation();
		if (APawn* Pawn = Cast<APawn>(GetOwner()))
		{
			SpawnRotation = Pawn->GetController()->GetControlRotation();
		}
		
		FActorSpawnParameters SpawnParms;
		SpawnParms.Owner = this;
		SpawnParms.Instigator = GetInstigator();
		
		GetWorld()->SpawnActor<ABullet>(
			BulletClass,
			SpawnLocation,
			SpawnRotation,
			SpawnParms
		);
	}
}

