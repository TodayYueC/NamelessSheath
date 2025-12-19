// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor/InteractActorBase.h"
#include "Character/HeroYue.h"
#include "Engine/Engine.h"
#include "Components/SphereComponent.h"
//#include "Character/HeroYue.h"
// Sets default values
AInteractActorBase::AInteractActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InteractMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractMesh"));
	RootComponent = InteractMesh;
	InteractActorName = FName("InteractActorBase");
	InteractStartComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InteractStartComponent"));
	InteractStartComponent->SetupAttachment(InteractMesh);
	InteractStartComponent->InitSphereRadius(200.0f);
	InteractStartComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	InteractStartComponent->SetGenerateOverlapEvents(true);
	
	
	
}

// Called when the game starts or when spawned
void AInteractActorBase::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,TEXT("BeginPlay") );
	InteractStartComponent->OnComponentBeginOverlap.AddDynamic(this,&AInteractActorBase::InteractOpen);
	InteractStartComponent->OnComponentEndOverlap.AddDynamic(this,&AInteractActorBase::InteractClose);
}

// Called every frame
void AInteractActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractActorBase::Interact_Implementation(APawn* Interactor)
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,TEXT("交互成功：基类实现") );
}

void AInteractActorBase::InteractOpen(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	
	if (OtherActor&& OtherActor != this&& OtherComp)
	{
		if (AHeroYue* Hero = Cast<AHeroYue>(OtherActor))
		{	
			GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Yellow,TEXT("进入交互范围") );
			Hero->bIsInteract = true;
			//IInteractInterface::Execute_Interact(this,Hero);
		}
	}
}

void AInteractActorBase::InteractClose(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
	if (OtherActor&& OtherActor != this&& OtherComp)
	{
		if (AHeroYue* Hero = Cast<AHeroYue>(OtherActor))
		{
			GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("离开交互范围") );
			Hero->bIsInteract = false;
		}
	}
}

