// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OpemDoor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
struct FTimerHandle;

UCLASS()
class NAMELESSSHEATH_API AOpemDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpemDoor();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	UStaticMeshComponent* OpenDoorMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	UBoxComponent* TriggerBox;
	
	UPROPERTY()
	FRotator NowRotator;
	UPROPERTY()
	FVector NowLocation;
	
	FTimerHandle TimerHandle;
	
	bool bIsInTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void OpenDoor();
	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void CloseDoor();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void OpenTrigger();
	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void CloseTrigger();
	
	UFUNCTION(BlueprintCallable, Category = "Door")
	void PlayDoor(float rotator);
	UFUNCTION(BlueprintCallable, Category = "Door")
	void PlayTrigger(float vector);
	
};
