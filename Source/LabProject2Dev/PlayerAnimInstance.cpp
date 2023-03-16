// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn && Player == nullptr)
		{
			Player = Cast<APlayerCharacter>(Pawn);
		}
	}
	IsAttack = false;
}

void UPlayerAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn && Player == nullptr)
		{
			Player = Cast<APlayerCharacter>(Pawn);
		}
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		Speed.Z = 0.f;
		MovementSpeed = Speed.Size();
	}
	if (Player)
	{
		IsAttack = Player->GetIsAttack();
	}

}

void UPlayerAnimInstance::ResetAttack()
{
	if (Player)
	{
		Player->ResetAttack();
	}
}
