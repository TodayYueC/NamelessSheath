// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyPlayerWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class NAMELESSSHEATH_API UMyPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateHealthBar(float CurrentHealth,float MaxHealth);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
};
