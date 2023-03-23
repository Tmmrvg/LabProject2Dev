// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"


class AMover;

/**
 * 
 */
UCLASS()
class LABPROJECT2DEV_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMyGameModeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawned Objects")
	TSubclassOf<AMover> Mover_BP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawned Objects")
	TArray<AMover*> Movers;

	TArray<AMover*> GetMovers();
	
};
