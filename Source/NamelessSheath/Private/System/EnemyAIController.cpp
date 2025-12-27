// Fill out your copyright notice in the Description page of Project Settings.


#include "System/EnemyAIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/HeroYue.h"
#include "Engine/Engine.h"

AEnemyAIController::AEnemyAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	
	if (Sight)
	{
		Sight->SightRadius = 2000.0f;
		Sight->LoseSightRadius = 2500.0f;
		
		Sight->PeripheralVisionAngleDegrees = 90.0f;
		Sight->DetectionByAffiliation.bDetectEnemies = true;
		Sight->DetectionByAffiliation.bDetectNeutrals = true;
		Sight->DetectionByAffiliation.bDetectFriendlies = true;
	}
	AIPerceptionComponent->ConfigureSense(*Sight);
	
	AIPerceptionComponent->SetDominantSense(Sight->GetSenseImplementation());
	
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (PerceptionComponent)
	{
		PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdated);
	}
	
	
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
	
	
	
	// if (APawn* EnemyPawn = GetPawn())
	// {
	// 	//MoveToLocation(EnemyPawn->GetActorLocation()+FVector(1000,0,0));
	// 	if (AHeroYue* Hero = Cast<AHeroYue>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	// 	{
	// 		MoveToActor(Hero);
	// 	}
	// }
}

void AEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (AHeroYue* Hero = Cast<AHeroYue>(Actor))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			//看见玩家，设置黑板键值
			GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"),Hero);
			GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,TEXT("看见玩家"));
		}
		else
		{
			if (GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")) == Hero)
			{
				//当前黑板键值是该玩家，才清除
				GetBlackboardComponent()->ClearValue(TEXT("TargetActor"));
				GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("失去玩家"));
			}
		}
	}
}
