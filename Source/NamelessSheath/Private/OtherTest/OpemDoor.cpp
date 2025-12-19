// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherTest/OpemDoor.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

// Sets default values
AOpemDoor::AOpemDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	OpenDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OpenDoorMesh"));
	OpenDoorMesh->SetupAttachment(RootComponent);
	OpenDoorMesh->SetCollisionProfileName(FName("BlockAll"));
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootComponent);
	DoorMesh->SetCollisionProfileName(FName("BlockAll"));
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AOpemDoor::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AOpemDoor::OnOverlapEnd);
	
	bIsInTime = false;
}

// Called when the game starts or when spawned
void AOpemDoor::BeginPlay()
{
	Super::BeginPlay();
	NowRotator = DoorMesh->GetRelativeRotation();
	NowLocation = OpenDoorMesh->GetRelativeLocation();
}

// Called every frame
void AOpemDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOpemDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	if (!bIsInTime)
	{
		OpenDoor();
		OpenTrigger();
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		bIsInTime = false;
	}
}

void AOpemDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{	
	if (!bIsInTime)
	{
		bIsInTime = true;
		GetWorldTimerManager().SetTimer(TimerHandle, [this]()
		{
			bIsInTime = false;
			CloseDoor();
			CloseTrigger();
		}, 3.0f, false);
	}
}

void AOpemDoor::PlayDoor(float rotator)
{
	
	FRotator NewRotator = NowRotator + FRotator(0.0f, rotator, 0.0f);
	DoorMesh->SetRelativeRotation(FRotator(NewRotator));
}

void AOpemDoor::PlayTrigger(float vector)
{
	
	FVector NewLocation = NowLocation + FVector(0.0f, 0.0f, vector);
	OpenDoorMesh->SetRelativeLocation(NewLocation);
}

