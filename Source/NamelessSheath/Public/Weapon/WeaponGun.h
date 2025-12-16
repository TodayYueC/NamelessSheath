// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponGun.generated.h"

class ABullet;

UCLASS()
class NAMELESSSHEATH_API AWeaponGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponGun();
	UPROPERTY(EditAnywhere,Category="BulletClass")
	TSubclassOf<ABullet> BulletClass;
	
	UPROPERTY()
	TObjectPtr<ABullet> Bullet;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,Category="WeaponGun")
	TObjectPtr<UStaticMeshComponent> GunMesh;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	void Fire();
	//FORCEINLINE UStaticMeshComponent* GetWeaponMesh()  { return GunMesh; }

};
