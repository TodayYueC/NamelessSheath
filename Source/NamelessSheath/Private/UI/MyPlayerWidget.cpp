// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyPlayerWidget.h"
#include "Components/ProgressBar.h"

void UMyPlayerWidget::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	if (HealthBar)
	{
		float Percent = CurrentHealth / MaxHealth;
		HealthBar->SetPercent(Percent);
	}
}
