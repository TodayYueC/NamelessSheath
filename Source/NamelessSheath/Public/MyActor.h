// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "MyActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOverlap,FString,MyString);

UCLASS()
class NAMELESSSHEATH_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();
	FOnOverlap OnOverlap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere,Category="Cube")
	TObjectPtr<UStaticMeshComponent> Cube;
	//test
	 // UPROPERTY(EditAnywhere,Category="Cube")
	 // UStaticMeshComponent* Cube1;
	
	UPROPERTY(VisibleAnywhere,Category="Cube")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(VisibleAnywhere,Category="Cube")
	TObjectPtr<USphereComponent> SphereComponentMin;
	
	UFUNCTION()
	void SayOverlap(FString MyString);
	
	UFUNCTION(Category="OverLap")
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);
	
	UFUNCTION(Category="OnHit")
	void OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere,Category="Force")
	FVector Force;
	UPROPERTY(EditAnywhere,Category="Force")
	FVector TForce;
	
	UPROPERTY(EditAnywhere,Category="Movement")
	FVector Movement;
	UPROPERTY(EditAnywhere,Category="Rotation")
	FRotator Rotation;
	
	UPROPERTY(EditAnywhere,Category="Movement")
	FVector MoveSpeed;
	UPROPERTY(EditAnywhere,Category="Rotation")
	FRotator RotateSpeed;
	
	
};


// UFUNCTION(BlueprintCallable,Category="MyFunction")
// void MyFunction();
//
// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MyInt",meta =(ClampMin = 0,ClampMax = 5,UIMin = 1,UIMax = 4))
// int MyReadWrite;
//
// UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="MyInt",meta =(ClampMin = 0,ClampMax = 5))
// int MyReadOnly;
//
// UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="MyInt")
// int MyDefaultsOnly;
//
// UPROPERTY(EditInstanceOnly,BlueprintReadWrite,Category="MyInt")
// int MyInstanceOnly;
//
// UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="MyInt")
// int MyVisibleAnywhere;
//
// UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite,Category="MyInt")
// int MyVisibleDefaults;
//
// UPROPERTY(VisibleInstanceOnly,BlueprintReadWrite,Category="MyInt")
// int MyVisibleInstance;