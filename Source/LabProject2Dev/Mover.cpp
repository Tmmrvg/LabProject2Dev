// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "MyGameModeBase.h"

// Sets default values
AMover::AMover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->SetupAttachment(GetRootComponent());
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AMover::OnOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AMover::OnComponentEndOverlap);

	Velocity = FVector();
	Acceleration = FVector();

	GameMode = nullptr;
	StandStill = false;
	mass = 10;
	MU = 0.1f;
	DragCoefficient = 0.1f;
	UniversalGravitationalConstant = 500.f;


	EnableAttractionGravity = false;
	Handled = false;
}

// Called when the game starts or when spawned
void AMover::BeginPlay()
{
	Super::BeginPlay();

	Collider->OnComponentBeginOverlap.AddDynamic(this, &AMover::OnOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AMover::OnComponentEndOverlap);
	Handled = false;

}

// Called every frame
void AMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (EnableAttractionGravity)
	{
		if (GameMode)
		{
			TArray<AMover*> Movers = GameMode->GetMovers();
			for (int i{}; i < Movers.Num(); i++)
			{
				if (Movers[i] != this)
				{					
					Movers[i]->Attract(this);
				}
			}
		}
	}

	// Add Acceleration
	if (!FMath::IsNearlyZero(Acceleration.X))
	{
		Velocity.X += Acceleration.X;
	}
	if (!FMath::IsNearlyZero(Acceleration.Y))
	{
		Velocity.Y += Acceleration.Y;
	}
	if (!FMath::IsNearlyZero(Acceleration.Z))
	{
		Velocity.Z += Acceleration.Z;
	}


	// Add Velocity
	if (!UKismetMathLibrary::Vector_IsNearlyZero(Velocity))
	{
		SetActorLocation(GetActorLocation() + (Velocity * DeltaTime));
	}



	Acceleration = FVector::ZeroVector;

}

void AMover::AddForce(FVector force)
{
	if (!StandStill)
	{
		force *= 100.f;
		if (!FMath::IsNearlyZero(mass))
		{

			Acceleration = force / mass;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Error: Mass is 0"));
		}
	}
	

}

void AMover::AddFriction()
{
	FVector Force = Velocity;
	Force.Normalize();
	Force *= -1.f;

	float normal = mass;

	Force *= MU * normal;

	AddForce(Force);
}

void AMover::AddDrag()
{
	FVector Force = Velocity;
	Force.Normalize();
	Force *= -0.5f;

	float speed = Velocity.Length();

	Force *= speed * DragCoefficient * speed;
	AddForce(Force);
}

void AMover::AddDrag(float dragCoefficient)
{
	FVector Force = Velocity;
	Force.Normalize();
	Force *= -0.5f;

	float speed = Velocity.Length();

	Force *= speed * dragCoefficient * speed;
	AddForce(Force);
}

void AMover::Attract(AMover* other)
{
	FVector direction = GetActorLocation() - other->GetActorLocation();

	float distanceSq = direction.Length() * direction.Length();
	distanceSq = FMath::Clamp(distanceSq, 100.f, 100000.f);

	direction.Normalize();

	float strength = mass * other->mass;
	strength *= UniversalGravitationalConstant;
	strength /= distanceSq;

	direction *= strength;
	other->AddForce(direction);

}

void AMover::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor->IsA<AMover>() && !Handled)
	{
		AMover* otherMover = Cast<AMover>(OtherActor);

		if (!StandStill && !otherMover->StandStill)
		{
			// Total Momentum = m1 * v1 + m2 * v2

			// en.wikipedia.org/wiki/Elastic_collision
			FVector MyVelocity = Velocity;
			FVector TheirVelocity = otherMover->Velocity;


			Velocity = (((mass - otherMover->mass) / (mass + otherMover->mass)) * MyVelocity) + (((2 * otherMover->mass) / (mass + otherMover->mass)) * TheirVelocity);


			otherMover->Velocity = ((2 * mass) / (mass + otherMover->mass)) * MyVelocity + ((otherMover->mass - mass) / (otherMover->mass + mass)) * TheirVelocity;



			otherMover->Handled = true;
			Handled = true;
		}
		
	}
}

void AMover::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{	
	Handled = false;
}

