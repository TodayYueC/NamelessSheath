// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Cube = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Cube"));
	RootComponent = Cube;
	
	Force = FVector(0.0f, 0.0f, 0.0f);
	TForce = FVector(0.0f, 0.0f, 0.0f);
	Movement = FVector(0.0f, 0.0f, 0.0f);
	Rotation = FRotator(0.0f, 0.0f, 0.0f);
	MoveSpeed = FVector(0.0f, 0.0f, 0.0f);
	RotateSpeed = FRotator(0.0f, 0.0f, 0.0f);
	

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	Cube->AddForce(Force,NAME_None,true);
	Cube->AddTorqueInRadians(TForce,NAME_None,true);
	// GEngine->AddOnScreenDebugMessage(1,3.0f,FColor::Purple,TEXT("Hello World from MyActor!"));
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewLocation = GetActorLocation();
	NewLocation += Movement * DeltaTime;
	SetActorLocation(NewLocation);
	
	FRotator NewRotation = GetActorRotation();
	NewRotation += Rotation * DeltaTime;
	SetActorRotation(NewRotation);//慎用，pitch yaw roll90度会出bug
	
	FVector Speed = MoveSpeed * DeltaTime;
	AddActorLocalOffset(Speed,true);
	
	FRotator RSpeed = RotateSpeed * DeltaTime;
	AddActorLocalRotation(RSpeed,true);
	
	
	 // UE_LOG(LogTemp, Warning, TEXT("Hello World from MyActor!"));
}

// void AMyActor::MyFunction()
// {
// 	GEngine->AddOnScreenDebugMessage(1,3.0f,FColor::Blue,TEXT("MyFuncyion Called!"));
// }

