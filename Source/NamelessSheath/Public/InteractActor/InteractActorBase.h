// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Universal/InteractInterface.h"

#include "InteractActorBase.generated.h"

class USphereComponent;

UCLASS()
class NAMELESSSHEATH_API AInteractActorBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractActorBase();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InteractActor")
	UStaticMeshComponent* InteractMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InteractActor")
	FName InteractActorName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InteractActor")
	USphereComponent* InteractStartComponent;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact_Implementation(APawn* Interactor) override;
	
	UFUNCTION()
	void InteractOpen(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult);
	UFUNCTION()
	void InteractClose(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
