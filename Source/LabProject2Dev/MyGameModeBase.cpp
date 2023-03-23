// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Mover.h"

AMyGameModeBase::AMyGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	int amount = 5;
	UWorld* world = GetWorld();
	for (int i{}; i < 5; i++)
	{
		float angle = FMath::RandRange(0, 360);
		float radian = angle * (PI / 180.f);

		FVector pos = FVector(cos(radian), sin(radian), 0);
		pos *= FMath::RandRange(500, 5000);
		AMover* mover = (AMover*)world->SpawnActor<AActor>(Mover_BP, pos, FRotator::ZeroRotator);
		mover->GameMode = this;
		mover->EnableAttractionGravity = true;
		FVector velocity = FVector::CrossProduct(pos, FVector(0, 0, 1));
		velocity.Normalize();
		velocity *= 1000.f;
		mover->Velocity = velocity;

		Movers.Add(mover);

	}
	
	AMover* sun = (AMover*)world->SpawnActor<AActor>(Mover_BP, FVector(0,0,0), FRotator::ZeroRotator);
	sun->GameMode = this;
	sun->EnableAttractionGravity = true;
	sun->mass = 100.f;
	sun->StandStill = true;
	sun->SetActorScale3D(FVector(3, 3, 3));
	Movers.Add(sun);
}

void AMyGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<AMover*> AMyGameModeBase::GetMovers()
{
	return Movers;
}
