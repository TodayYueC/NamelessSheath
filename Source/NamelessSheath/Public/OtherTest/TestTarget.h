// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestTarget.generated.h"

class UNiagaraSystem;

UCLASS()
class NAMELESSSHEATH_API ATestTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<UStaticMeshComponent>TargetMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth;
	
	UPROPERTY(EditAnywhere,Category = "VFX")
	TObjectPtr<UNiagaraSystem> ExplosionVFX;
	
	UPROPERTY(EditAnywhere,Category = "Sound")
	TObjectPtr<USoundBase> ExplosionSound;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
