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

UCLASS()
class NAMELESSSHEATH_API AHeroYue : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHeroYue();
	
	bool bIsInteract;
	void Interact();
	void DoInteract();
	AActor* TargetInteractActor;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);
	
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
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

private:
	UPROPERTY(VisibleAnywhere,Category="Camera",meta=(AllowPrivateAccess="true"))
	TObjectPtr<USpringArmComponent> MySpringArm;
	UPROPERTY(VisibleAnywhere,Category="Camera",meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCameraComponent> MyCamera;
	
	
};
