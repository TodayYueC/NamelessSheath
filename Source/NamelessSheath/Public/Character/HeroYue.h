// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "HeroYue.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AWeaponGun;
class UHealthComponent;
UCLASS()
class NAMELESSSHEATH_API AHeroYue : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHeroYue();
	
	bool bIsInteract;
	void Interact();
	void HealthCast();
	void DoInteract();
	AActor* TargetInteractActor;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartFire(const FInputActionValue& Value);
	void OnFire(const FInputActionValue& Value);
	void StopFire(const FInputActionValue& Value);
	
	float InteractionTime = 0.0f;
	
	//射线检测通用函数
	UFUNCTION(BlueprintCallable,Category="LineTrace")
	bool DoLineTrace(FHitResult& OutHit,float TraceDistance);
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> HeroIMC;
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> HeroMove;
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> HeroLook;
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> HeroJump;
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> HeroShot;
	
	UPROPERTY(EditAnywhere,Category="Weapon")
	TSubclassOf<AWeaponGun> WeaponClass;
	
	UPROPERTY()
	TObjectPtr<AWeaponGun> CurrentWeapon;
	
	UPROPERTY(VisibleAnywhere,Category="HealthComponent")
	TObjectPtr<UHealthComponent> HealthComponent;
	
	UPROPERTY(EditAnywhere,Category="MontageFire")
	TObjectPtr<UAnimMontage> MontageFire;
	
	float DefaultArmLength;
	
	UPROPERTY(EditAnywhere,Category="Firetime")
	float AimArmLength = 80.0f;
	
	UPROPERTY(EditAnywhere,Category="Firetime")
	float FireInterpSpeed = 20.0f;
	
	bool bIsAiming = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE UHealthComponent* GetHealthComponent() const { return HealthComponent; }
	

private:
	UPROPERTY(VisibleAnywhere,Category="Camera",meta=(AllowPrivateAccess="true"))
	TObjectPtr<USpringArmComponent> MySpringArm;
	UPROPERTY(VisibleAnywhere,Category="Camera",meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCameraComponent> MyCamera;
	
	float Firetime = 0.0f;
	bool bCanFire = false;
	
	
};
