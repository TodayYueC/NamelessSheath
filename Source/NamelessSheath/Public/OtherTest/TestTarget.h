// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestTarget.generated.h"

class UNiagaraSystem;
class UHealthComponent;
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
	
	
	UPROPERTY(EditAnywhere,Category = "VFX")
	TObjectPtr<UNiagaraSystem> ExplosionVFX;
	
	UPROPERTY(EditAnywhere,Category = "Sound")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HealthComponent")
	TObjectPtr<UHealthComponent> HealthComponent;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	FORCEINLINE UHealthComponent* GetHealthComponent() const { return HealthComponent; }

};
