// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherTest/HitTarget.h"

// Sets default values
AHitTarget::AHitTarget()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHitTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHitTarget::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

