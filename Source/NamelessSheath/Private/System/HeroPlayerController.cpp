// Fill out your copyright notice in the Description page of Project Settings.


#include "System/HeroPlayerController.h"
#include "UI/MyPlayerWidget.h"
#include "Character/HeroYue.h"
#include "Component/HealthComponent.h"

void AHeroPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (PlayerWidgetClass)
	{
		PlayerWidget = CreateWidget<UMyPlayerWidget>(this, PlayerWidgetClass);
		if (PlayerWidget)
		{	
			PlayerWidget->AddToViewport();
			
		}
	}
	AHeroYue* MyHero = GetPawn<AHeroYue>();
	if (MyHero)
	{
		UHealthComponent* HealthComp = MyHero->GetHealthComponent();
		if (HealthComp)
		{
			HealthComp->OnHealthChanged.AddDynamic(this, &AHeroPlayerController::OnHealthChanged);
			if (PlayerWidget)
			{
				float CurrentHealth = HealthComp->GetCurrentHealth();
				float MaxHealth = HealthComp->GetMaxHealth();
				PlayerWidget->UpdateHealthBar(CurrentHealth, MaxHealth);
			}
		}
	}
}

void AHeroPlayerController::OnHealthChanged(float CurrentHealth, float MaxHealth, AActor* InstigatorActor,
	float HealthDelta)
{
	if (PlayerWidget){
		PlayerWidget->UpdateHealthBar(CurrentHealth,MaxHealth);
	}
}
