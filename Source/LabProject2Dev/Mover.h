// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mover.generated.h"


class USphereComponent;
class AMyGameModeBase;


UCLASS()
class LABPROJECT2DEV_API AMover : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMover();

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	USphereComponent* Collider;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "My Physics")
	float mass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My Physics")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My Physics")
	FVector Acceleration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My Physics")
	FVector GravityVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My Physics")
	bool EnableAttractionGravity;

	bool Handled;
	bool StandStill;
	float MU;
	float DragCoefficient;
	float UniversalGravitationalConstant;

	AMyGameModeBase* GameMode;
	


	void AddForce(FVector force);

	void AddFriction();
	void AddDrag();
	void AddDrag(float dragCoefficient);

	void Attract(AMover* other);



	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
