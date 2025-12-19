// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor/Door.h"

ADoor::ADoor()
{
	InteractActorName = FName("Door");
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

void ADoor::Interact_Implementation(APawn* Interactor)
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Blue,TEXT("交互成功：门被打开") );
}
