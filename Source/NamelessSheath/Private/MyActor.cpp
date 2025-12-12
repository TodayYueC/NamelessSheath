// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h"
#include "Components/SphereComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Cube = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Cube"));
	RootComponent = Cube;
	// Cube1 = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Cube99"));
	// Cube1->SetupAttachment(Cube);
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponentMin = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponentMin"));
	SphereComponent->SetupAttachment(Cube);
	SphereComponent->SetSphereRadius(192);
	SphereComponentMin->SetupAttachment(Cube);
	SphereComponentMin->SetSphereRadius(96);
	
	SphereComponent->SetCollisionProfileName(TEXT("Trigger"));
	SphereComponent->SetGenerateOverlapEvents(true);
	
	SphereComponentMin->SetCollisionProfileName(TEXT("BlockAll"));
	SphereComponentMin->SetNotifyRigidBodyCollision(true);
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AMyActor::OnBeginOverlap);
	this->OnOverlap.AddDynamic(this,&AMyActor::SayOverlap);
	SphereComponentMin->OnComponentHit.AddDynamic(this,&AMyActor::OnHit);
	
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

void AMyActor::SayOverlap(FString MyString)
{
	
	GEngine->AddOnScreenDebugMessage(2,3.0f,FColor::Blue,MyString);
}

void AMyActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Green,TEXT("重叠对象：") + OtherActor->GetName());
	
		FString MyString= TEXT("重叠事件广播");
		if (OnOverlap.IsBound())
		{
			OnOverlap.Broadcast(MyString);
		}
		GEngine->AddOnScreenDebugMessage(1,3.0f,FColor::Red,TEXT("重叠开始！"));
	}
}

void AMyActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Yellow,TEXT("碰撞对象：") + OtherActor->GetName());
		GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Cyan,TEXT("碰撞发生！"));
	}
}


// void AMyActor::MyFunction()
// {
// 	GEngine->AddOnScreenDebugMessage(1,3.0f,FColor::Blue,TEXT("MyFuncyion Called!"));
// }

