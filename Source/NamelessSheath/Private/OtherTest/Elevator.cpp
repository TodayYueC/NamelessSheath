// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherTest/Elevator.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ElevatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElevatorMesh"));
	RootComponent = ElevatorMesh;
	
}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	NowLocation = ElevatorMesh->GetRelativeLocation();
	TargetLocation = NowLocation + FVector(0.0f,-800.0f,800.0f);
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ElevatorMesh->SetRelativeLocation(FMath::VInterpTo(ElevatorMesh->GetRelativeLocation(),TargetLocation,DeltaTime,1.0f));
	if (ElevatorMesh->GetRelativeLocation().Equals(TargetLocation))
	{
		ElevatorMesh->SetRelativeLocation(TargetLocation);
		FVector NewLocation = ElevatorMesh->GetRelativeLocation();
		TargetLocation = NowLocation;
		NowLocation = NewLocation;
		
	}
	

}

