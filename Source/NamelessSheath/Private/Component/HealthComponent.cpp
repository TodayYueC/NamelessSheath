// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

bool UHealthComponent::ApplyHealthChange(float HealthDelta, AActor* InstigatorActor)
{
	//无敌判断，预留，暂未实现
	//预留旧血量
	float OldHealth = CurrentHealth;
	//修改血量
	CurrentHealth = FMath::Clamp(CurrentHealth + HealthDelta, 0.0f, MaxHealth);
	//计算血量变化值
	float ActualDelta = CurrentHealth - OldHealth;
	//广播血量变化事件
	if (ActualDelta != 0)
	{
		OnHealthChanged.Broadcast(CurrentHealth, MaxHealth, InstigatorActor, ActualDelta);
	}
	//返回是否成功修改血量
	return ActualDelta != 0.0f;
	

}

