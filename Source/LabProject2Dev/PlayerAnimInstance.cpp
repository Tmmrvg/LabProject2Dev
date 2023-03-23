// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "PlayerCharacter.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	isAttacking = false;
	
	Super::NativeInitializeAnimation();
	
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
		Player = Cast<APlayerCharacter>(Pawn);
		}
	}
}

void UPlayerAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner(); // Inherited from UAnimInstance
	}
	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();
	}

	if (Player)
	{
		
	}
}

void UPlayerAnimInstance::ResetAttack()
{
	if (Player)
	{
		Player->ResetAttack();
	}
}
