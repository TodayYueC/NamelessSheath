// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HeroYueAnim.generated.h"

class ACharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class NAMELESSSHEATH_API UHeroYueAnim : public UAnimInstance
{
	GENERATED_BODY()	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	
protected:
	UPROPERTY(visibleAnywhere,BlueprintReadOnly,Category="Character")
	TObjectPtr<ACharacter> MyHero;
	UPROPERTY(visibleAnywhere,BlueprintReadOnly,Category="Character")
	TObjectPtr<UCharacterMovementComponent> MyHeroMovement;
	UPROPERTY(visibleAnywhere,BlueprintReadOnly,Category="Character")
	float Speed;
	UPROPERTY(visibleAnywhere,BlueprintReadOnly,Category="Character")
	bool bIsInAir;
};
