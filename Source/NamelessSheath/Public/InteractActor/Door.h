// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActor/InteractActorBase.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class NAMELESSSHEATH_API ADoor : public AInteractActorBase
{
	GENERATED_BODY()
public:
	ADoor();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Interact_Implementation(APawn* Interactor) override;	
};
