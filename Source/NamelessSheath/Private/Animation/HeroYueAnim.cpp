// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HeroYueAnim.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UHeroYueAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	MyHero = Cast<ACharacter>(TryGetPawnOwner());
	if (MyHero)
	{
		MyHeroMovement = MyHero->GetCharacterMovement();
	}
}

void UHeroYueAnim::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (MyHero == nullptr)
	{
		MyHero = Cast<ACharacter>(TryGetPawnOwner());
		if (MyHero)
		{
			MyHeroMovement = MyHero->GetCharacterMovement();
		}
	}
	
	if (MyHero == nullptr||MyHeroMovement == nullptr)
	{
		return;
	}
	
	Speed = MyHeroMovement->Velocity.Size2D();
	bIsInAir = MyHeroMovement->IsFalling();
}