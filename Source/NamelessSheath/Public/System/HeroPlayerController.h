// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HeroPlayerController.generated.h"

class UMyPlayerWidget;

/**
 * 
 */
UCLASS()
class NAMELESSSHEATH_API AHeroPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,Category="UI")
	TSubclassOf<UUserWidget> PlayerWidgetClass;	
	
protected:
	virtual void BeginPlay() override;	
	
	UFUNCTION()
	void OnHealthChanged(float CurrentHealth,float MaxHealth,AActor* InstigatorActor,float HealthDelta);

private:
	UPROPERTY()
	TObjectPtr<UMyPlayerWidget> PlayerWidget;
	
	
	
	
};
